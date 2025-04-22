#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

#define h0 PIN_B4
#define h1 PIN_B5
#define h2 PIN_B6
#define h3 PIN_B7

unsigned int8 mqcot[] = {0b1110, 0b1101, 0b1011, 0b0111};

unsigned int8 doi_ma_phim[] = { 
   1, 2, 3, 0xA, 
   4, 5, 6, 0xB, 
   7, 8, 9, 0xC, 
   0xE, 0, 0xF, 0xD 
};

unsigned int8 ma7doan[] = { 
   0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
   0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};

unsigned int8 mp = 0xFF;

unsigned int quet_mtp_4x4() {
   unsigned int maphim = 0xFF;
   unsigned int8 hang, cot;

   for (cot = 0; cot < 4; cot++) {
      output_b(mqcot[cot]);
      delay_us(100);

      if (!input(h0)) { hang = 0; }
      else if (!input(h1)) { hang = 1; }
      else if (!input(h2)) { hang = 2; }
      else if (!input(h3)) { hang = 3; }
      else { continue; } 

      delay_ms(20);

      if (!input(h0 + hang)) { 
         maphim = cot * 4 + hang;
         maphim = doi_ma_phim[maphim];
         break;
      }
   }
   return maphim;
}

void main() {
   set_tris_b(0xF0); // B4-B7 
   port_b_pullups(0xF0); // B4-B7
   set_tris_d(0x00); // 7SEG LED 
   output_d(0x00);

   while (TRUE) {
      mp = quet_mtp_4x4();
      if (mp != 0xFF) {
         output_d(ma7doan[mp]);
      } else {
         output_d(0x00);
      }
   }
}


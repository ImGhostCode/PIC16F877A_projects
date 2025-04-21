#include <16f877A.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

unsigned int8 i,d;

void main() {
   set_tris_d(0x00);
   d=0x00;
   output_d(d);
   delay_ms(500);
   while(true) {
      for(i = 0; i < 8; i++) {
         d = (d<<1) + 0x01;
         output_d(d);
         delay_ms(500);
      }
      for(i = 0; i < 8; i++) {
         d = d<<1;
         output_d(d);
         delay_ms(500);
      }
   }
}

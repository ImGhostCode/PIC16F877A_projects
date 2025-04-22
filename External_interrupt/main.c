#include <main.h>
unsigned INT count, ma_ch, ma_dv, i;
int1 int0;
const unsigned char ma7doan[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

#int_ext
void interrupt_int0()
{
   IF (!input (PIN_B0))
   {
      int0 = 1;
   }
}

void giaima_2so_xvn(unsigned int8 x) 
{
   ma_dv = ma7doan[x % 10]; 
   ma_ch = ma7doan[x / 10];
   if (x < 10)
   {
      ma_ch = 0x00;
   }
}

void hienthi_2so_quet() 
{
   output_d(ma_dv);
   output_high(PIN_C0);
   delay_ms(2);
   output_low(PIN_C0);

   output_d(ma_ch);
   output_high(PIN_C1);
   delay_ms(2);
   output_low(PIN_C1);
}

void main()
{
   set_tris_b (0x01) ;
   set_tris_d (0x00) ;
   set_tris_c (0x00) ;
   output_d(0x00);
   
  // port_b_pullups(0x01);
   enable_interrupts (INT_EXT_H2L) ;
   count = 0; int0 = 0;
   WHILE (TRUE)
   {
      enable_interrupts (GLOBAL) ;
      giaima_2so_xvn (count) ;
      hienthi_2so_quet () ;

      IF (int0 == 1)
      {
         disable_interrupts (GLOBAL) ;
         count++; int0 = 0;
         IF (count > 99) count = 0;
         giaima_2so_xvn (count) ;
         FOR (i = 0; i < 50; i++)
         {
            hienthi_2so_quet () ;
         }
      }
   }
}


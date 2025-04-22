
#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp

unsigned INT T0;
unsigned int ma_tr, ma_ch, ma_dv;
const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; 

void giaima_3so_xvn(signed int16 x)
{
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[ (x / 10) % 10];
   ma_tr = ma7doan[ (x / 100) % 10]; 
   if (x < 100)
   {
      ma_tr = 0x00;
   }
   if (x < 10)
   {
      ma_ch = 0x00;
   }
}

void hienthi_3so_quet() 
{
   output_b (0x00) ;

   output_d (ma_dv);
   output_high (PIN_B0);
   delay_ms (2);
   output_low (PIN_B0);

   output_d (ma_ch);
   output_high (PIN_B1);
   delay_ms (2);
   output_low (PIN_B1);

   output_d (ma_tr);
   output_high (PIN_B2);
   delay_ms (2);
   output_low (PIN_B2);
}

void main()
{
   set_tris_b (0x00);
   set_tris_d (0x00);
   output_d (0x00) ;
   setup_timer_0 (T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0 (0);

   while (TRUE)
   {
            T0 = get_timer0 ();
            giaima_3so_xvn (T0) ;
      hienthi_3so_quet ();
   }
}


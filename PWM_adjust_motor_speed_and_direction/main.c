
#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#define forw PIN_B0
#define rev PIN_B1

unsigned int ma_ch, ma_dv;
signed int16 capdo=0;
const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void giaima_capdo_2so_xvn(signed int16 x) 
{
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[x / 10 % 10];
   if (x < 10) ma_ch = 0x00;
}

void hienthi_capdo() 
{
   output_d (ma_dv) ;
   output_high (PIN_B2) ;
   delay_ms (1) ;
   output_low (PIN_B2) ;
   
   output_d (ma_ch) ;
   output_high (PIN_B3) ;
   delay_ms (1) ;
   output_low (PIN_B3) ;
}
void delay_hienthi() 
{
   unsigned int j;
   for (j = 0; j < 50; j++) hienthi_capdo ();
}

void phim_forw() 
{
   if (capdo < 20)
   {
      capdo++;
      set_pwm1_duty (capdo * 50) ;
      giaima_capdo_2so_xvn (capdo);
      delay_hienthi ();
      } else {
      hienthi_capdo ();
   }
}

void phim_rev() 
{
   if (capdo < 20)
   {
      capdo++;
      set_pwm2_duty (capdo * 50) ;
      giaima_capdo_2so_xvn (capdo);
      delay_hienthi ();
      } else {
      hienthi_capdo ();
   }
}

void dongco_stop() 
{
   capdo = 0;
   set_pwm1_duty (0);
   set_pwm2_duty (0);
   giaima_capdo_2so_xvn (capdo);
   hienthi_capdo ();
}

void main()
{
   set_tris_b (0x03);
   set_tris_d (0x00);
   set_tris_c (0x00);
   output_d (0x00);
   output_high (PIN_C0);
   setup_ccp1 (CCP_PWM);
   setup_ccp2 (CCP_PWM);
   setup_timer_2 (T2_DIV_BY_16, 249, 1);
   capdo = 0;
   set_pwm1_duty (0);
   set_pwm2_duty (0) ;
   giaima_capdo_2so_xvn (capdo);

   while (TRUE)
   {
      if (!input (forw)) phim_forw ();
      else if (!input (rev)) phim_rev ();
      else dongco_stop () ;
   }
}


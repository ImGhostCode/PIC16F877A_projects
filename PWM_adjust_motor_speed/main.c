
#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp

#define up PIN_B0
#define stop PIN_B1
#define down PIN_B2

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
   output_high (PIN_C0) ;
   delay_ms (1) ;
   output_low (PIN_C0) ;
   output_d (ma_ch) ;
   output_high (PIN_C1) ;
   delay_ms (1) ;
   output_low (PIN_C1) ;
}

void delay_hienthi() 
{
   unsigned int j;
   for (j = 0; j < 10; j++) hienthi_capdo ();
}

void phim_up() 
{
   if (!input (up))
   {
      delay_hienthi () ;

      if (!input (up))
      {
         if (capdo < 20)
         {
            capdo++;
            set_pwm1_duty (capdo * 50) ;
            giaima_capdo_2so_xvn (capdo);
            do hienthi_capdo () ;
            while (!input (up));
         }
      }
   }
}

   
void phim_down() 
{
   if (!input (down))
   {
      delay_hienthi () ;

      if (!input (down))
      {
         if (capdo > 0)
         {
            capdo--;
            set_pwm1_duty (capdo * 50) ;
            giaima_capdo_2so_xvn (capdo);
            do hienthi_capdo () ;
            while (!input (down));
         }
      }
   }
}

   
void phim_stop() 
{
   if (!input (stop))
   {
      capdo = 0;
      set_pwm1_duty (0);
      giaima_capdo_2so_xvn (capdo);
   }
}

void main()
{
   set_tris_b (0xff);
   set_tris_d (0x00);
   set_tris_c (0x00);
   output_c (0x00);
   output_d (0x00);
   output_high (PIN_C4);
   output_low (PIN_C2);
   setup_ccp1 (CCP_PWM);
   setup_timer_2 (T2_DIV_BY_16, 249, 1);
   capdo = 0;
   set_pwm1_duty (0);
   giaima_capdo_2so_xvn (capdo);

   while (TRUE)
   {
      phim_up () ;
      phim_down () ;
      phim_stop () ;
      hienthi_capdo () ;
   }
}


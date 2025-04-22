
#include <main.h>

unsigned int ma_ch, ma_dv, i, mp;
unsigned int8 gh;
const unsigned char ma7doan[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

unsigned int8 d;
#INT_RB
void rb_isr() 
{
//!   delay_ms (20);
//!   if (!input (PIN_B0)) mp = 0;
//!   else if (!input (PIN_B1)) mp = 1;
//!   while (!input (PIN_B0) || ! input (PIN_B1));
d = ~d;
output_d(d);
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
   output_d (ma_dv) ;
   output_high (PIN_C0) ;
   delay_ms (2) ;
   output_low (PIN_C0) ;
   output_d (ma_ch) ;
   output_high (PIN_C1) ;
   delay_ms (2) ;
   output_low (PIN_C1) ;
}

void main()
{
d = 0x00;
   set_tris_b (0x03);
   set_tris_d (0x00);
   set_tris_c (0x00);
   output_d (0x00) ;
clear_interrupt(INT_RB);        // Clear PORTB IOC flag bit
enable_interrupts(INT_RB);      // Enable PORTB IOC
enable_interrupts(GLOBAL);      // Enable global interrupts
   gh = 0; mp = 0xff;
   while (TRUE);
//!   {
//!      giaima_2so_xvn (gh) ;
//!      hienthi_2so_quet () ;
//!
//!      if (mp != 0xff)
//!      {
//!         disable_interrupts (GLOBAL) ;
//!         if (mp == 0) gh--;
//!         else if (mp == 1) gh++;
//!         if (gh > 99) gh = 0;
//!         else if (gh < 0) gh = 99;
//!         giaima_2so_xvn (gh) ;
//!         for (i = 0; i < 50; i++)
//!         {
//!            hienthi_2so_quet () ;
//!         }
//!
//!         mp = 0xff;
//!         enable_interrupts (GLOBAL) ;
//!      }

}


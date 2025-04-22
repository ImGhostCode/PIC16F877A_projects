#include <16F877A.h>
#fuses HS, NOWDT, PUT, NOPROTECT, NOLVP
#use delay(clock=6MHz)

volatile unsigned int8 giay = 0, bdt = 0;
unsigned int8 ma_ch, ma_dv;
const unsigned char ma7doan[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

#define TIMER1_PRELOAD 18658

#int_TIMER1
void interrupt_timer1() 
{
   bdt++;
   set_timer1(TIMER1_PRELOAD);
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
   output_high(PIN_B0);
   delay_ms(2);
   output_low(PIN_B0);

   output_d(ma_ch);
   output_high(PIN_B1);
   delay_ms(2);
   output_low(PIN_B1);
}

void main()
{
   set_tris_b(0x00);
   set_tris_d(0x00);
   output_d(0x00);
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(TIMER1_PRELOAD);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);

   giaima_2so_xvn(giay);

   while (TRUE)
   {
      hienthi_2so_quet();

      if (bdt >= 4) 
      {
         bdt = 0;
         giay++;
         if (giay >= 60) giay = 0;
         giaima_2so_xvn(giay);
      }
   }
}


// 16bit => 65,536
// 6MHz => 1/4 => 1.5MHz => 1/8 => 187.5kHz => 5.33us
//   250ms / 5.33us = 93,808
// TMR1= 65,536 - 46,878 = 18,658

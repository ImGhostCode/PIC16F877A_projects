#include <16F877A.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)
#bit tmr1if = 0x0c.0
unsigned INT d,b,i;

#INT_timer1
void interupt_timer1() 
{

   d = ~d;
   output_d (d) ;
}

void main()
{
   set_tris_b(0x00);
   b = 0xff;
   output_b (b) ;
   set_tris_d (0x00) ;
   d = 0xff;
   output_d (d) ;
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_8) ;
   set_timer1 (18658) ;
   tmr1if= 0;
   enable_interrupts (GLOBAL) ;
   enable_interrupts (INT_TIMER1) ;
   
    WHILE (TRUE)
   {
      FOR (i = 0; i < 8; i++)
      {
         b = (b<<1);
         output_b (b) ;
         delay_ms (300) ;
      }

      FOR (i = 0; i < 8; i++)
      {
         b = (b<<1) + 1;
         output_b (b) ;
         delay_ms (300) ;
      }
   }
}
// 16bit => 65,536
// 6MHz => 1/4 => 1.5MHz => 1/8 => 187.5kHz => 5.33us
//   250ms / 5.33us = 93,808
// TMR1= 65,536 - 46,878 = 18,658




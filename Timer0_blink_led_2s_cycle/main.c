
#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)
#bit tmr0if = 0x0b.2

unsigned INT d, bdt;

void main()
{
   set_tris_d (0x00) ;
   d = 0x00;
   output_d (d) ;
   setup_timer_0 (T0_INTERNAL|T0_DIV_256) ;
   set_timer0 (0) ;
   bdt = 0;

   WHILE (TRUE)
   {
      IF (tmr0if == 1)
      {
         bdt++;
         tmr0if = 0;
         set_timer0(0);
         if (bdt == 23) {
            d = ~d;
            output_d (d) ;
            bdt = 0;
         }
      }
   }
}

// 6MHz => 1/4 => 1.5MHz
// 1.5Mhz / 256 => 5.860kHz
// 1 / 5.860kHz => 170.7us
// 170.7us * 256 = 43.699us = 43.7ms 
// 1s / 43.7ms = 23

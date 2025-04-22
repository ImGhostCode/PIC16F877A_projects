#include <main.h>
#bit tmr1if = 0x0c.0

unsigned INT d;

void main()
{
   set_tris_d (0x00) ;
   d = 0x00;
   output_d (d) ;
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_8) ;
   set_timer1 (0) ;

   WHILE (TRUE)
   {
      IF (tmr1if == 1)
      {
         d = ~d;
         output_d (d) ;
         tmr1if = 0;
      }
   }
}
// 6MHz => 1/4 => 1.5MHz => 1/8 => 187.5kHz => 5.33us * 65,536 => 349,5ms => T= 699ms

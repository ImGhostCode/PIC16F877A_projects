
#include <main.h>
#bit tmr1if = 0x0c.0

unsigned int d;

#int_timer1
void interupt_timer1() 
{
   d = ~d;
   output_d (d);
}

void main()
{
   set_tris_d (0x00);
   d = 0xff;
   output_d (d);
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_8);
   set_timer1 (0);
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   while (TRUE);
}

// 6MHz => 1/4 => 1.5MHz => 1/8 => 187.5kHz => 5.33us * 65,536 => 349,5ms => T= 699ms


#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)
#define on PIN_B0
#define off PIN_B1

void main()
{
   set_tris_b (0x03);
   set_tris_d (0x00);

   while (TRUE)
   {
      output_d (0xff);
      while (input (on)) ;
      output_d (0x00);
      while (input (off));
   }
}


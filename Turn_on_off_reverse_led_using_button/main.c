#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

#define on PIN_B0
#define off PIN_B1
#define inv PIN_B2

unsigned int8 d=0;

void chongdoi_inv() 
{
   if (!input (inv))
   {
      delay_ms (20);

      if ( ! input (inv))
      {
         d = ~d;
         output_d (d);
         while ( ! input (inv)) ;
      }
   }
}

void main()
{
   set_tris_b (0x07);
   set_tris_d (0x00);

   while (TRUE)
   {
      d = 0xff;
      output_d (d);
      while (input (on)) ;
      d = 0xf0;
      output_d (d);

      do
      {
         chongdoi_inv ();
      } while (input (off));
   }
}


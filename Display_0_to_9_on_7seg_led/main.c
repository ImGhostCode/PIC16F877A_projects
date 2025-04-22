#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; 
signed int dem;
void main()
{
   set_tris_d(0x00);
   while(TRUE)
   {
   for(dem= 0; dem <10; dem++){
      output_d(ma7doan[dem]);
      delay_ms(300);
   }
   }

}

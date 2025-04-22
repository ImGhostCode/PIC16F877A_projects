#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f}; // 0,1,2,3
const unsigned char maquet[4] = {0x01, 0x02, 0x04, 0x08};

void hienthi_1_led(int8 j) 
{
   output_b (0x00);
   output_d (ma7doan[j]);
   output_b (maquet[j]);
   delay_ms (5);
}

void main()
{
   set_tris_b (0x00); 
   set_tris_d (0x00);

   while (TRUE)
   {
      for (int8 j = 0; j < 4; j++)
      {
         hienthi_1_led(j);
      }
   }
}


#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; 
signed int dem;
unsigned int8 ma_ch, ma_dv;

void giaima_2so_xvn(signed int16 x) 
{
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[x / 10];

   if (ma_ch == 0x3f) 
   {
      ma_ch = 0x00;
   }
}

void hienthi_2so_quet() 
{
   output_d (ma_dv);
   output_high (PIN_B0);
   delay_ms (3);
   output_low (PIN_B0);

   output_d (ma_ch);
   output_high (PIN_B1);
   delay_ms (3);
   output_low (PIN_B1);
}

void main()
{
   set_tris_b (0x00);
   set_tris_d (0x00);

   while (TRUE)
   {
      // 0 - 99
      for (dem = 0; dem < 100; dem++)
      {
         giaima_2so_xvn(dem);
         
         
         for (int i = 0; i < 100; i++)
         {
            hienthi_2so_quet();
         }
      }
      
      // 99 - 0
      // for (dem = 99; dem > -1; dem--)
      // {
      //   giaima_2so_xvn(dem);
         
      //   for (int i = 0; i < 100; i++) 
      //   {
      //      hienthi_2so_quet();
      //  }
      // }
   }
}


#include <main.h>
#fuses hs, nowdt, put, noprotect, nolvp
#use delay(clock=6MHz)

#define up PIN_B0
#define down PIN_B1

unsigned int16 gh = 0;
unsigned char ma7doan[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned int ma_tr, ma_ch, ma_dv;

int1 up_last = 1, down_last = 1;
unsigned int16 counter_up = 0, counter_down = 0;

void giaima_3so_xvn(signed int16 x) 
{
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[(x / 10) % 10];
   ma_tr = ma7doan[(x / 100) % 10];

   if (x < 100) ma_tr = 0x00;
   if (x < 10) ma_ch = 0x00;
}

void hienthi_3so_quet() 
{
   output_d(ma_dv);
   output_high(PIN_E0);
   delay_ms(2);
   output_low(PIN_E0);

   output_d(ma_ch);
   output_high(PIN_E1);
   delay_ms(2);
   output_low(PIN_E1);

   output_d(ma_tr);
   output_high(PIN_E2);
   delay_ms(2);
   output_low(PIN_E2);
}

void phim_up()
{
   if (!input(up))  
   {
      if (up_last)
      {
         gh++;
         counter_up = 0;
         up_last = 0;
      }
      else
      {
         counter_up++;
         if (counter_up > 150)  // Sau khoảng 300ms, tăng nhanh
         {
            gh++;
            delay_ms(50);
         }
      }
   }
   else
   {
      up_last = 1;
      counter_up = 0;
   }
}

void phim_down() 
{
   if (!input(down))  
   {
      if (down_last)
      {
         gh--;
         counter_down = 0;
         down_last = 0;
      }
      else
      {
         counter_down++;
         if (counter_down > 150) 
         {
            gh--;
            delay_ms(50);
         }
      }
   }
   else
   {
      down_last = 1;
      counter_down = 0;
   }
}

void main()
{
   set_tris_b(0x03);
   set_tris_e(0x00);
   set_tris_d(0x00);
   gh = 0;

   while (TRUE)
   {
      phim_up();
      phim_down();
      giaima_3so_xvn(gh);
      hienthi_3so_quet();
   }
}


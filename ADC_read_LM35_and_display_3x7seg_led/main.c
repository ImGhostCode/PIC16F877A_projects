#include <main.h>
#define solando 100

unsigned INT16 lm35;
unsigned INT j, ma_tr, ma_ch, ma_dv;
const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; 

void giaima_3so_xvn(signed int16 x) 
{
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[ (x / 10) % 10];
   ma_tr = ma7doan[ (x / 100) % 10];
   if (x < 100)
   {
      ma_tr = 0x00;
   }
   if (x < 10)
   {
      ma_ch = 0x00;
   }
}

void hienthi_3so_quet() 
{
   output_d (ma_dv) ;
   output_high (PIN_B0) ;
   delay_ms (3) ;
   output_low (PIN_B0) ;

   output_d (ma_ch) ;
   output_high (PIN_B1) ;
   delay_ms (3) ;
   output_low (PIN_B1) ;

   output_d (ma_tr) ;
   output_high (PIN_B2) ;
   delay_ms (3) ;
   output_low (PIN_B2) ;
}

void main()
{
   set_tris_a(0x01);
   set_tris_d(0x00);

   setup_adc(ADC_CLOCK_DIV_8);
  setup_adc_ports(AN0);
   set_adc_channel(0);
   delay_us(20); // Small delay to allow ADC channel to stabilize

   WHILE (TRUE)
   {
      lm35 = 0;
      FOR (j = 0; j < solando; j++)
      {
         lm35 = lm35 + read_adc();
         delay_us(10); // Small delay between readings
      }

      lm35 = lm35 / solando;
      lm35 = lm35 / 2.046;
      giaima_3so_xvn(lm35);
      hienthi_3so_quet();
   }
}

// Vref- = 0V, Vref+ = 5V
// SS = (Vref+ - Vref-) / (2^10-1) = 5000mV/1023 = 4,887mV
// FS = SS * 1023 = 4.887mV * 1023 = 5000mV
// Do phan giai = 10mV / 4.887mV = 2.046

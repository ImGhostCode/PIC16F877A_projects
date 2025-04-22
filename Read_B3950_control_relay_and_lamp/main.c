
#include <main.h>
#include <math.h>
#define SOLANDO 10
#define RELAY PIN_A3
#define HIGH_TEMP 40
#define LOW_TEMP 38
#define R1 10000
#define BETA 3950
#define T0 298.15
#define R25 10000

float logR2, R2, T;
unsigned int16 ntc_value;
unsigned int j, ma_tr, ma_ch, ma_dv;
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
   output_d (ma_dv);
   output_high (PIN_B0);
   delay_ms (1);
   output_low (PIN_B0);

   output_d (ma_ch);
   output_high (PIN_B1);
   delay_ms (1);
   output_low (PIN_B1);

   output_d (ma_tr);
   output_high (PIN_B2);
   delay_ms (1);
   output_low (PIN_B2);
}

void sosanh_dk_den() 
{
   if (ntc_value > HIGH_TEMP)
   {
      output_low (RELAY); // Turn relay OFF (assuming low output activates relay)
      } else if (ntc_value < LOW_TEMP) {
      output_high (RELAY); // Turn relay ON
   }
}

void main() 
{
   set_tris_a (0x01); // RA0 as input (ADC), others as output
   output_a (0x00) ;
   set_tris_b (0x00) ;
   output_b (0x00) ;
   set_tris_d (0x00) ;
   output_d (0x00) ;
   setup_adc (ADC_CLOCK_DIV_8); // Use slower ADC clock for better accuracy
   setup_adc_ports (AN0); // Correct syntax for CCS C
   set_adc_channel (0) ;
   delay_us (20); // Initial delay for ADC to stabilize
   while (TRUE)
   {
      ntc_value = 0;
      for (j = 0; j < SOLANDO; j++)
      {
         unsigned int16 adc_value = read_adc ();
         float voltage = adc_value * (5.0 / 1023.0); 
         R2 = R1 * (5.0 / voltage - 1.0); 
         logR2 = log (R2 / R25);
         T = 1.0 / ((logR2 / BETA) + (1.0 / T0)); 
         ntc_value += (T - 273.15);
         delay_us (10) ;
      }

      ntc_value /= SOLANDO;
      giaima_3so_xvn (ntc_value) ;
      hienthi_3so_quet () ;
      sosanh_dk_den () ;
      
   }
}


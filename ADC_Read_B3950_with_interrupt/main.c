#include <main.h>
#include <math.h>

#define SOLANDO 10
#define R1 10000    
#define BETA 3950  
#define T0 298.15  
#define R25 10000  

unsigned int32 adc_sum = 0;
unsigned int16 adc_value;
float logR2, R2, T;
signed int16 ntc_value;  // Cho ph�p gi� tr? �m n?u c?n
unsigned int j, ma_tr, ma_ch, ma_dv;
const unsigned char ma7doan[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

#INT_AD
void interrupt_adc() {
   adc_sum += read_adc(ADC_READ_ONLY);
   j++;
}

void giaima_3so_xvn(signed int16 x) {
   if (x < 0) x = 0;  // Tr�nh s? �m kh�ng hi?n th? du?c
   ma_dv = ma7doan[x % 10];
   ma_ch = ma7doan[(x / 10) % 10];
   ma_tr = ma7doan[(x / 100) % 10];
   
   if (x < 100) ma_tr = 0x00;
   if (x < 10) ma_ch = 0x00;
}

void hienthi_3so_quet() {
   output_d(ma_dv);
   output_high(PIN_B0);
   delay_ms(1);
   output_low(PIN_B0);

   output_d(ma_ch);
   output_high(PIN_B1);
   delay_ms(1);
   output_low(PIN_B1);

   output_d(ma_tr);
   output_high(PIN_B2);
   delay_ms(1);
   output_low(PIN_B2);
}

void main() {
   set_tris_b(0x00);
   output_b(0x00);
   set_tris_a(0x01);
   set_tris_d(0x00);
   output_d(0x00);
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   delay_us(20);

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_AD);
   j = 0;
   ntc_value = 0;
   giaima_3so_xvn(ntc_value);

   while (TRUE) {
      if (j < SOLANDO) {
         hienthi_3so_quet();
         read_adc(ADC_START_ONLY);
      } else {
         adc_value = adc_sum / SOLANDO;
         adc_sum = 0;

         float voltage = adc_value * (5.0 / 1023.0);
         R2 = R1 * (5.0 / voltage - 1.0);
         logR2 = log(R2 / R25);
         T = 1.0 / ((logR2 / BETA) + (1.0 / T0));
         ntc_value = (signed int16)(T - 273.15);

         giaima_3so_xvn(ntc_value);
         
         j = 0;
         delay_us(10);
      }
   }
}


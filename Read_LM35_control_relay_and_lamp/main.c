#include <main.h>
#define SOLANDO 100
#define RELAY PIN_A3
#define HIGH_TEMP 40
#define LOW_TEMP 38

unsigned int16 lm35_raw; // Store raw ADC value
unsigned int16 lm35_temp; // Store calculated temperature
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

void sosanh_dk_den() {
    if (lm35_temp > HIGH_TEMP) {
        output_low(RELAY); // Turn relay OFF (assuming low output activates relay)
    } else if (lm35_temp < LOW_TEMP) {
        output_high(RELAY); // Turn relay ON
    }
}

void main() {
    set_tris_a(0x01); // RA0 as input (ADC), others as output
    set_tris_b(0x00);
    set_tris_d(0x00);

    setup_adc(ADC_CLOCK_DIV_8); // Use slower ADC clock for better accuracy
    setup_adc_ports(AN0); // Correct syntax for CCS C
    set_adc_channel(0);
    delay_us(20); // Initial delay for ADC to stabilize

    while (TRUE) {
        lm35_raw = 0;
        for (j = 0; j < SOLANDO; j++) {
            set_adc_channel(0); // Ensure channel is selected before each read
            delay_us(20); // Acquisition time is crucial!
            lm35_raw += read_adc();
            delay_us(10); // Small delay between readings within the loop
            hienthi_3so_quet();
        }

        lm35_raw = lm35_raw / SOLANDO;
        lm35_temp = lm35_raw * 0.488; // Calibration for LM35 (10mV/�C, 5V reference, 10-bit ADC)

        giaima_3so_xvn(lm35_temp);
        sosanh_dk_den();

        delay_ms(100); // Add a small delay to avoid excessive display updates
    }
}

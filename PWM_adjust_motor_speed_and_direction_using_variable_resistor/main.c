
#include <main.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP 
#define LCD_ENABLE_PIN  PIN_A3
#define LCD_RS_PIN      PIN_A5
#define LCD_RW_PIN      PIN_A4
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7 
#include <lcd.c>
#define forw PIN_B5
#define stop PIN_B6
#define revs PIN_B7
#define solando 10

unsigned int j, mp,ht, ma_ng, ma_tr, ma_ch, ma_dv;
unsigned int16 vr, capdo;
const unsigned int lcd_h0[] ={"PIC16F877A"};
const unsigned int lcd_h1[] = {"DK TDO DCO:"};
#int_RB
void rb_isr(void)
{
   delay_ms(50);

   if (!input (forw))
   {
      mp = 0;
      ht = 0;
   }

   else if (!input (stop))
   {
      mp = 1;
      ht = 1;
   }

   else if (!input (revs))
   {
      mp = 2;
      ht = 2;
   };

   clear_interrupt (int_RB) ;
}

void giaima_capdo_4so_xvn(unsigned int16 x) 
{
   ma_dv = x % 10 + 0x30;
   ma_ch = x / 10 % 10 + 0x30;
   ma_tr = x / 100 % 10 + 0x30;
   ma_ng = x / 1000 % 10 + 0x30;
   
   if (ma_ng == 0x30)
   {
      ma_ng = ' ';

      if (ma_tr == 0x30)
      {
         ma_tr = ' ';
         if (ma_ch == 0x30) ma_ch = ' ';
      }
   }
}

void lcd_hien_thi_3_che_do() 
{
   if (ht == 0)
   {
      lcd_gotoxy (12, 0) ;
      lcd_putc ("Forw");
      
      } else if (ht == 1){
      lcd_gotoxy (12, 0) ;
      lcd_putc ("Stop");
   } else

   if (ht == 2)
   {
      lcd_gotoxy (12, 0) ;
      lcd_putc ("Prev");
   }

   ht = 3;
}

void lcd_hienthi_capdo() 
{
   lcd_gotoxy (12, 1) ;
   lcd_putc (ma_ng) ;
   lcd_putc (ma_tr) ;
   lcd_putc (ma_ch) ;
   lcd_putc (ma_dv) ;
}

void doc_hthi_bien_tro() 
{
   vr = 0;
   for (j = 0; j < solando; j++)
   {
      vr = vr + read_adc (ADC_READ_ONLY);
   }

   vr = vr / solando;
   capdo = vr;
   giaima_capdo_4so_xvn (capdo);
   lcd_hienthi_capdo () ;
   delay_ms (20);
}

void xu_ly_3_che_do()
{
   if (mp == 0)
   {
      set_pwm2_duty (0);
      set_pwm1_duty (capdo);
   } else if (mp == 1)

   {
   set_pwm1_duty (0);
   set_pwm2_duty (0);
   } else if (mp == 2)

   {
   set_pwm1_duty (0);
   set_pwm2_duty (capdo);
   }
}

void main()
{
   set_tris_a (0x04);
   set_tris_b (0xff);
   set_tris_c (0x00);
   set_tris_d (0x00);
   clear_interrupt(int_RB);        // Clear PORTB IOC flag bit
   enable_interrupts(int_RB);      // Enable PORTB IOC
   enable_interrupts(GLOBAL);      // Enable global interrupts
   port_b_pullups (0xff);
   
   output_high (PIN_C0);
   setup_ccp1 (CCP_PWM);
   setup_ccp2 (CCP_PWM);
   setup_timer_2 (T2_DIV_BY_16, 249, 1);
   set_pwm1_duty (0);
   set_pwm2_duty (0);
   
   setup_adc (ADC_CLOCK_DIV_8);
   setup_adc_ports (AN0);
   set_adc_channel (0);
   mp = 1; ht = 1;
   
   lcd_init ();
   lcd_putc ('\f'); // Clear LCD
   lcd_gotoxy (1, 1) ;
   for (j = 0; j < 10; j++) lcd_putc (lcd_h0[j]);
   lcd_gotoxy (1, 0) ;
   for (j = 0; j < 11; j++) lcd_putc (lcd_h1[j]);
   while (TRUE)
   {
      lcd_hien_thi_3_che_do ();
      xu_ly_3_che_do ();
      read_adc (ADC_START_ONLY) ;
      doc_hthi_bien_tro ();
   }
}


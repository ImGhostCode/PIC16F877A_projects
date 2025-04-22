
#include <16F877A.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock = 6MHz)
#define LCD_ENABLE_PIN  PIN_A3
#define LCD_RS_PIN      PIN_A5
#define LCD_RW_PIN      PIN_A4
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7 
#include <lcd.c>

unsigned int phut,giay;

void lcd_hienthi() 
{
   lcd_gotoxy (12, 1);
   lcd_putc ((phut / 10) + 0x30);
   lcd_putc ((phut % 10) + 0x30);
   lcd_putc (":") ;
   lcd_putc ((giay / 10) + 0x30);
   lcd_putc ((giay % 10) + 0x30);
}

void main()
{
   lcd_init ();
   lcd_putc ('\f'); // Clear LCD
   lcd_gotoxy (1, 1) ;
   lcd_putc ("CLOCK:");
   lcd_gotoxy (1, 0) ;
   lcd_putc ("HO THANH LIEM");
   phut = 0;
   giay = 0;

   while (true)
   {
      lcd_hienthi ();
      delay_ms (1000);
      giay++;

      if (giay == 60)
      {
         giay = 0;
         phut++;
         if (phut == 60) phut = 0;
      }
   }
}


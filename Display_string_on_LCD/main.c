
#include <hien_thi_chuoi_lcd.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP 
#define LCD_ENABLE_PIN  PIN_A3
#define LCD_RS_PIN      PIN_A5
#define LCD_RW_PIN      PIN_A4
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7 
#include <lcd.c>

void main()
{
   set_tris_d (0x00) ;
   set_tris_a (0x00) ;
   lcd_init ();
   lcd_putc ('\f'); // Clear LCD
   
   //!   lcd_gotoxy (1, 1) ;
   // ! for (i = 0; i < 16; i++)
   // {
      //!      lcd_putc(hang0[i]);

      // !
   // }

   //!   lcd_gotoxy(1,0);
   // ! for (i = 0; i < 16; i++)
   // {
      //!      lcd_putc(hang1[i]);

      // !
   //}

   
   lcd_putc (" HO THANH LIEMM ") ;
   lcd_gotoxy (1, 0) ;
   lcd_putc (" WELCOME TO MCU ") ;
   while (TRUE) ;
}


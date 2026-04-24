#include "lcd.h"


//helper functions 
static void clock_pulse(void)
{
  LCD_CTRL_PORT |= ( 1 << PIN_E);
  _delay_us(2);
  LCD_CTRL_PORT &= ~(1 << PIN_E);
}

static void wait_until_ready(void)
{
  LCD_DATA_DDR = 0x00; // set data bus as input
  LCD_CTRL_PORT |= (1 << PIN_RW); //RW = 1 (read)
  LCD_CTRL_PORT &= ~(1 << PIN_RS); // instruction mode

  while (LCD_DATA_PIN & 0x80)
    clock_pulse();
  LCD_DATA_DDR = 0xFF;
}

//public functions
void lcd_command(unsigned char cmd)
{
  wait_until_ready();
  LCD_DATA_PORT = cmd;
  LCD_CTRL_PORT &= ~(1 << PIN_RW);
  LCD_CTRL_PORT &= ~(1 << PIN_RS);
  clock_pulse();
  LCD_DATA_PORT = 0;
}

void lcd_print(unsigned char ch)
{
  wait_until_ready();
  LCD_DATA_PORT = ch;
  LCD_CTRL_PORT &= ~(1 << PIN_RW);//write 
  LCD_CTRL_PORT |=  (1 << PIN_RS);//data
  clock_pulse();
  LCD_DATA_PORT = 0;
}

void lcd_print_string(const char *str)
{
  while (*str)
  {
    lcd_print(*str++);
  }
}

void lcd_set_cursor(unsigned char row, unsigned char col)
{
  unsigned char address;

  if (row == 0 )
    address = 0x00 + col;
  else
    address = 0x40 + col; 
  lcd_command(0x80 | address);
}
/* For init i used the 8 bit mode and based on the datasheet 
 * the steps of powering an lcd goes like 
 * 1. wait for power to settle 
 * 2. function set (8-bit, 2 lines, 5x8 font)
 * 3. clear display
 * 4. display on, cursor on, blink on
 * 5. entry mode (increment, no shift)
 */

void lcd_init(void)
{
  LCD_DATA_DDR = 0xFF;
  LCD_DATA_DDR |= (1 << PIN_E) | (1 << PIN_RW) | (1 << PIN_RS);
  _delay_ms(20);
  lcd_command(0x38) // set the screen for 8bit mode and 2 lines
  _delay_us(50);
  lcd_command(0x01); // clear display 
  _delay_ms(2);
  lcd_command(0x06); // increment & no shift mode
  _delay_us(50);
}
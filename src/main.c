#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
  // Initialize the LCD
  lcd_init();
  
  // Display text on first line
  lcd_set_cursor(0, 0);
  lcd_print_string("Hello");
  
  // Display text on second line
  lcd_set_cursor(1, 0);
  lcd_print_string("World");
  
  // Main loop
  while (1)
  {
    // Add your application code here
  }
  
  return 0;
}

#pragma once 

#include <avr/io.h>
#include <util/delay.h>

// pin mapping
#define LCD_CTRL_DDR      DDRD
#define LCD_CTRL_PORT     PORTD
#define LCD_DATA_DDR      DDRB
#define LCD_DATA_PORT     PORTB
#define LCD_DATA_PIN      PINB

#define PIN_E             5 // falling edge 
#define PIN_RS            2 // 0 for instruction & 1 for data
#define PIN_RW            7 // 0 for write & 1 for read ( for example check if the lcd is busy)


// functions 

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_print_char(unsigned char ch);
void lcd_print_string(const char *str);
void lcd_set_cursor(unsigned char row, unsigned char col);

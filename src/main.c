#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define lcdcontrolpinout DDRD
#define lcdcontrolhighlow PORTD
#define lcddatapinout DDRB
#define lcddatahighlow PORTB
#define clock 5 //E PIN ---data reads when falling edge 
#define rs 2 //instruction = 0 | data = 1 
#define rw 7 //read = 1 | write = 0

void LCD_command(unsigned char command);
void LCD_print(unsigned char character);
void check_if_busy();
void clockset();

int main()
{
	lcddatapinout |= 0xFF;
	lcdcontrolpinout |= ( 1 << clock) | ( 1 << rw) | ( 1 << rs);
	_delay_ms(20);
	LCD_command(0x38);
	_delay_us(20);
	LCD_command(0x01);
	_delay_us(20);
	LCD_command(0x0F);
	LCD_print(0x41);
	
	while(1)
	{
		
	}
	
}
void LCD_command(unsigned char command)
{
	check_if_busy();
	lcddatahighlow = command;
	lcdcontrolhighlow &= ~(1 << rw);
	lcdcontrolhighlow &= ~(1 << rs);
	clockset();
	lcddatahighlow = 0;
}
void LCD_print(unsigned char character)
{
	check_if_busy();
	lcddatahighlow = character;
	lcdcontrolhighlow &= ~(1 << rw);
	lcdcontrolhighlow |= (1 << rs);
	clockset();
	lcddatahighlow = 0;
}
void check_if_busy()
{
	lcddatapinout = 0x00;
	lcdcontrolhighlow |= 1 << rw;
	lcdcontrolhighlow &= ~(1 << rs);
	while(PINB >= 0x80)
	{
		clockset();
	}
	lcddatapinout = 0xFF;
}
void clockset()
{
	lcdcontrolhighlow |= 1 << clock;
	_delay_us(2);
	lcdcontrolhighlow &= ~( 1 << clock);
}

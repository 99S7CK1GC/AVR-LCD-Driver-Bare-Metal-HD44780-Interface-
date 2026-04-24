# AVR-LCD-Driver-Bare-Metal-HD44780-Interface-
# avr-lcd

Bare-metal HD44780 LCD driver for AVR (ATmega328P), written in plain C.  
No Arduino libraries, no HAL — just direct register access.

## wiring

| LCD pin | AVR pin  | signal |
|---------|----------|--------|
| D0–D7   | PB0–PB7  | data bus |
| E       | PD5      | enable (clock) |
| RS      | PD2      | 0 = instruction / 1 = data |
| RW      | PD7      | 0 = write / 1 = read |
| VSS     | GND      | |
| VDD     | +5V      | |
| V0      | pot wiper| contrast |
| A/K     | +5V/GND  | backlight |

## api

```c
void lcd_init(void);                              // power-on init
void lcd_command(unsigned char cmd);              // send raw instruction
void lcd_print(unsigned char ch);                 // send one character
void lcd_set_cursor(unsigned char row, unsigned char col); // 0-indexed
```

## build

```bash
# 1. compile
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wall -o lcd_demo.elf main.c lcd.c
 
# 2. convert to hex
avr-objcopy -O ihex lcd_demo.elf lcd_demo.hex
 
# 3. flash  (change /dev/ttyUSB0 to your port)
avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -b 115200 -U flash:w:lcd_demo.hex
 
# 4. clean up
rm lcd_demo.elf lcd_demo.hex
 
```

## files

```
avr-lcd/
├── lcd.h      hardware defines + public api
├── lcd.c      driver implementation
├── main.c     usage example
```
still underprogress and next is to add a makefile and custom characters support 

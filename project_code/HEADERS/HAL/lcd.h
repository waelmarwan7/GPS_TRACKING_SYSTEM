
#ifndef LCD_H_
#define LCD_H_

#define lcd_Clear            0x01          // replace all characters with ASCII 'space'
#define lcd_Home             0x02          // return cursor to first position on first line
#define lcd_EntryMode        0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff       0x08          // turn display off
#define lcd_DisplayOn        0x0F          // display on & cursor blink
#define Set5x7FontSize       0x20                    // set font size to 5x7
#define four_bit_mode                0x28                    // select 4-bit mode
#define lcd_FunctionReset    0x30          // reset the LCD
#define eight_bit_mode       0x38          // 8-bit data, 2-line display, 5 x 7 font
#define first_row            0x80          // set cursor position in first row
#define second_row           0xC0          // set cursor position in second row
#define CURSOR_OFF           0x0C                    // Cursor off
#define CURSOR_ON            0x0E                    // Cursor on
#define EN                                   0x04                    // lcd enable
#define RS                                   0x01                    // register select






void SysTick_Init(void);
void delay_us(int count);
void delay_ms(int count);
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_write(unsigned char c, unsigned char ctrl);
void lcd_char(unsigned char data, unsigned char ctrl);
void lcd_str( char *str);



#endif /* LCD_H_ */

#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdint.h>
#include "hardware/i2c.h"

// Hardware Definitions
#define I2C_PORT i2c0
#define I2C_ADDR 0x27

#define PIN_SDA 4
#define PIN_SCL 5

// PCF8574 Module Bitmasks
#define MASK_RS (1 << 0)
#define MASK_RW (1 << 1)
#define MASK_E  (1 << 2)
#define MASK_BL (1 << 3)

// HD44780 LCD Commands
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME   0x02
#define LCD_ENTRY_MODE    0x04
#define LCD_DISPLAY_CTRL  0x08
#define LCD_FUNCTION_SET  0x20

#define LCD_DISPLAY_ON    0x04
#define LCD_CURSOR_OFF    0x00
#define LCD_BLINK_OFF     0x00

// Public Function Declarations
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_char(uint8_t ch);
void lcd_string(const char *s);
void lcd_set_cursor(int row, int col);
void clear_lcd(void);

#endif // LCD_I2C_H

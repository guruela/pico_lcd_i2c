#include "lcd_i2c.h"
#include "pico/stdlib.h"

// Writes a single byte directly to the PCF8574 I2C module
static void i2c_write_byte(uint8_t val) {
    i2c_write_blocking(I2C_PORT, I2C_ADDR, &val, 1, false);
}

// Pulses the Enable pin (High then Low) to make the LCD read data
static void lcd_toggle_enable(uint8_t val) {
    sleep_us(600);
    i2c_write_byte(val | MASK_E);      // Enable HIGH
    sleep_us(600);
    i2c_write_byte(val & ~MASK_E);     // Enable LOW
    sleep_us(600);
}

// Packages 4 data bits with RS mode and Backlight state, then sends it
static void lcd_send_nibble(uint8_t nibble, uint8_t mode) {
    uint8_t byte = (nibble & 0xF0) | mode | MASK_BL;
    i2c_write_byte(byte);
    lcd_toggle_enable(byte);
}

// Splits a standard 8-bit byte into upper and lower nibbles
static void lcd_send_byte(uint8_t val, uint8_t mode) {
    lcd_send_nibble(val, mode);        // Send upper 4 bits
    lcd_send_nibble(val << 4, mode);   // Shift and send lower 4 bits
}

// Sends a configuration command to the LCD (RS = 0)
void lcd_command(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
}

// Sends a text character to the LCD (RS = 1)
void lcd_char(uint8_t ch) {
    lcd_send_byte(ch, MASK_RS);
}

// Prints an entire string of text
void lcd_string(const char *s) {
    while(*s) {
        lcd_char(*s++);
    }
}

// Positions the cursor at a specific row (0-1) and column (0-15)
void lcd_set_cursor(int row, int col) {
    int row_offsets[] = { 0x00, 0x40 };
    lcd_command(0x80 | (col + row_offsets[row]));
}

// Clears the screen and resets cursor position
void clear_lcd(void) {
    lcd_command(LCD_CLEAR_DISPLAY);
    sleep_ms(2); // Clear command needs a longer delay to execute
}

// Hardware initialization sequence
void lcd_init(void) {
    sleep_ms(50); // Wait for power to stabilize
    
    // Reset sequence: Force 8-bit mode 3 times to clear garbage states
    lcd_send_nibble(0x30, 0);
    sleep_ms(5);
    lcd_send_nibble(0x30, 0);
    sleep_us(200);
    lcd_send_nibble(0x30, 0);
    sleep_ms(5);
    
    // Switch LCD into 4-bit mode
    lcd_send_nibble(0x20, 0);
    sleep_ms(5);

    // Configure display settings
    lcd_command(LCD_FUNCTION_SET | 0x08);  // Set to 2 lines, 5x8 font
    lcd_command(LCD_DISPLAY_CTRL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF); // Screen ON, Cursor OFF
    clear_lcd();                           // Clear display memory
    lcd_command(LCD_ENTRY_MODE | 0x02);    // Set cursor to auto-increment right
}

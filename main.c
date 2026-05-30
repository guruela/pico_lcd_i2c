#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd_i2c.h"

int main() {
    stdio_init_all();

    // Initialize physical I2C0 pins at 100 kHz
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);

    // Initialize the LCD
    lcd_init();

    // Write Text
    lcd_set_cursor(0, 0);
    lcd_string("Hello, Pico!");
    
    lcd_set_cursor(1, 2);
    lcd_string("I2C Driver OK");

    while (1) {
        tight_loop_contents();
    }
}

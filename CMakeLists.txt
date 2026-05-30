cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(lcd_i2c_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(lcd_i2c
    lcd_i2c.c
    main.c
)

target_link_libraries(lcd_i2c pico_stdlib hardware_i2c)

pico_enable_stdio_usb(lcd_i2c 1)
pico_enable_stdio_uart(lcd_i2c 1)
pico_add_extra_outputs(lcd_i2c)

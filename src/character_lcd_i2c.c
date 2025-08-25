/**
 * @file character_lcd_i2c.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 24/08/2025 - 22:17
 * @brief Character LCD library write functions implementation when the
 * display is interfaced through I2C.
 */

#include "character_lcd_i2c.h"

#define LCD_I2C_BYTES_PER_WRITE 4

static inline void lcd_write(uint8_t address, uint8_t *src, uint8_t length)
{
    return;
}

void lcd_write_instruction(character_lcd_t *display,
                       enum lcd_instruction instruction)
{
    uint8_t data_frame[LCD_I2C_BYTES_PER_WRITE] = {
        LCD_START_INSTRUCTION_REGISTER_WRITE | HIGH_NIBBLE(instruction),
        LCD_END_INSTRUCTION_REGISTER_WRITE | HIGH_NIBBLE(instruction),
        LCD_START_INSTRUCTION_REGISTER_WRITE | LOW_NIBBLE(instruction),
        LCD_END_INSTRUCTION_REGISTER_WRITE | LOW_NIBBLE(instruction)
    };
    lcd_write(display->address, data_frame, LCD_I2C_BYTES_PER_WRITE);
}

void lcd_write_data(character_lcd_t *display, uint8_t data)
{
    uint8_t data_frame[LCD_I2C_BYTES_PER_WRITE] = {
        LCD_START_DATA_REGISTER_WRITE | HIGH_NIBBLE(data),
        LCD_END_DATA_REGISTER_WRITE | HIGH_NIBBLE(data),
        LCD_START_DATA_REGISTER_WRITE | LOW_NIBBLE(data),
        LCD_END_DATA_REGISTER_WRITE | LOW_NIBBLE(data)
    };
    lcd_write(display->address, data_frame, LCD_I2C_BYTES_PER_WRITE); 
}

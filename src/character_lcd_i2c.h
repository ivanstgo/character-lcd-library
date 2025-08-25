/**
 * @file character_lcd_i2c.h
 * @autor Iván Santiago (gh: ivanstgo)
 * @date 24/08/2025 - 21:40
 * @brief This file defines the read and write functions of the character LCD
 * library when the display is interfaced through I2C serial interface.
 */

#ifndef __CHARACTER_LCD_I2C_H
#define __CHARACTER_LCD_I2C_H

#include "character_lcd_common.h"

/**
 * @brief This struct describes the number of display lines, the start memory
 * address of each line and the I2C address;
 */
typedef struct character_lcd
{
    /**
     * @brief Number of display lines
     */
    uint8_t lines;
    /**
     * @brief Array containing the character number at wich starts each line.
     */
    uint8_t *line_offsets;
    /**
     * @brief Display I2C address;
     */
    uint8_t address;
} character_lcd_t;

/**
 * @brief This enumeration lists the values of the HD44780 control signals
 * to perform read/write operations on both, IR (instruction register) and DR
 * (data register). Bit 0 = **RS**, bit 1 = **R/W**, bit 2 = **EN** and
 * bit 3 = **BL**.
 */
enum lcd_control
{
    LCD_START_INSTRUCTION_REGISTER_WRITE = 0b1100,
    LCD_END_INSTRUCTION_REGISTER_WRITE = 0b1000,
    LCD_START_DATA_REGISTER_WRITE = 0b1101,
    LCD_END_DATA_REGISTER_WRITE = 0b1001,
    LCD_START_INSTRUCTION_REGISTER_READ = 0b1110,
    LCD_END_INSTRUCTION_REGISTER_READ = 0b1010,
    LCD_START_DATA_REGISTER_READ = 0b1111,
    LCD_END_DATA_REGISTER_READ = 0b1011
};

/**
 * @brief Writes an instruction to the HD44780 controller.
 * @param display Pointer to character_lcd struct.
 * @param instruction Intruction to be written.
 */
void lcd_write_instruction(character_lcd_t *display,
                       enum lcd_instruction instruction);

/**
 * @brief Writes a byte to the HD44780 DDRAM.
 * @param display Pointer to character_lcd struct.
 * @param data Data to be written.
 */
void lcd_write_data(character_lcd_t *display, uint8_t data);

#endif /* !__CHARACTER_LCD_I2C_H */

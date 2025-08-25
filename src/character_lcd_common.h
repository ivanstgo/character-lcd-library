/**
 * @file character_lcd_common.h
 * @author Iván Santiago (gh: ivanstgo)
 * @date 24/08/2025 - 21:32
 * @brief Character LCD library common macros, enumerations and data structures.
 */
#ifndef __CHARACTER_LCD_COMMON_H
#define __CHARACTER_LCD_COMMON_H

#include <stdint.h>

/**
 * @brief This macro takes the least significant nibble from a byte.
 * @param BYTE An 8-bit integer.
 */
#define LOW_NIBBLE(BYTE) ((BYTE) & 0x0F)

/**
 * @brief This macro takes the most significant nibble from a byte.
 * @param BYTE An 8-bit integer.
 */
#define HIGH_NIBBLE(BYTE) ((BYTE) >> 4u)

/**
 * @brief HD44780 CGRAM address.
 */
typedef struct lcd_cgram_address
{
    /** @brief CGRAM address is 6-bit wide */
    uint8_t value : 6;
} lcd_cgram_address_t;

/**
 * @brief HD44780 DDRAM address.
 */
typedef struct lcd_ddram_address
{
    /** @brief DDRAM address is 7-bit wide */
    uint8_t value : 7;
} lcd_ddram_address_t;

/**
 * @brief HD44780 Address counter and busy flag.
 */
typedef struct lcd_address_counter
{
    uint8_t address_counter : 7;
    uint8_t busy_flag : 1;
} lcd_address_counter_t;

/**
 * @brief HD44780 Instructions.
 */
enum lcd_instruction
{
    /** @brief Clears the entire display and sets the cursor position to 0. */
    LCD_CLEAR_DISPLAY = 0b1,
    /** @brief Sets the cursor position to 0 and returns the display from
     * being shifted without changing DDRAM contents.
     */
    LCD_RETURN_HOME = 0b10,
    /** @brief Configures the cursor to decrement its position when a
     * read/write operation is performed. (I/D = 0; S = 0)
     */
    LCD_SET_ENTRY_MODE_DECREMENT_CURSOR_POSITION = 0b100,
    /** @brief Configures the cursor to increment its position when a
     * read/write operation is performed. (I/D = 1; S = 0)
     */
    LCD_SET_ENTRY_MODE_INCREMENT_CURSOR_POSITION = 0b110,
    /** @brief Configures the display to shift to the right when a
     * read/write operation is performed. (I/D = 0; S = 1)
     */
    LCD_SET_ENTRY_MODE_SHIFT_DISPLAY_TO_THE_RIGHT = 0b101,
    /** @brief  Configures the display to shift to the left when a
     * read/write operation is performed. (I/D = 1; S = 1)
     */
    LCD_SET_ENTRY_MODE_SHIFT_DISPLAY_TO_THE_LEFT = 0b111,
    /** @brief  Sets the entire display off. (D = 0; C = 0; B = 0) */
    LCD_DISPLAY_OFF = 0b1000,
    /** @brief  Sets the entire display on. (D = 1; C = 0; B = 0) */
    LCD_DISPLAY_ON = 0b1100,
    /** @brief  Sets the entire display on and enables blinking of cursor
     * position character. (D = 1; C = 0; B = 1)
     */
    LCD_DISPLAY_ON_BLINK_CURSOR = 0b1101,
    /** @brief  Sets the entire display on and sets cursor on.
     * (D = 1; C = 1; B = 0)
     */
    LCD_DISPLAY_ON_SHOW_CURSOR = 0b1110,
    /** @brief  Sets the entire display on, sets cursor on and enables blinking
     * of cursor position character. (D = 1; C = 1; B = 1) 
     */
    LCD_DISPLAY_ON_BLINK_AND_SHOW_CURSOR = 0b1111,
    /** @brief  Moves the cursor position to the left without changing DDRAM
     * contents. (S/C = 0; R/L = 0)
     */
    LCD_MOVE_CURSOR_TO_THE_LEFT = 0b10000, 
    /** @brief  Moves the cursor position to the right without changing
     * DDRAM contents. (S/C = 0; R/L = 1)
     */
    LCD_MOVE_CURSOR_TO_THE_RIGHT = 0b10100,
    /** @brief  Shifts the display to the left without changing DDRAM
     * contents. (S/C = 1; R/L = 0)
     */
    LCD_SHIFT_DISPLAY_TO_THE_LEFT = 0b11000,
    /** @brief  Shifts the display to the right without changing
     * DDRAM contents. (S/C = 1; R/L = 1)
     */
    LCD_SHIFT_DISPLAY_TO_THE_RIGHT = 0b11100,
    /** @brief  Sets interface data length to be 4-bit wide and selects
     * 1 display line and a 5x8 dots character font. (DL = 0; N = 0; F = 0)
     */
    LCD_SET_FUNCTION_4BIT_INTERFACE_ONE_DISPLAY_LINE_5X8_FONT = 0b100000,
    /** @brief  Sets interface data length to be 4-bit wide and selects
     * 2 display lines and 5x8 dots character font. (DL = 0; N = 1; F = 0)
     */
    LCD_SET_FUNCTION_4_BIT_INTERFACE_TWO_DISPLAY_LINE_5X8_FONT = 0b101000,
    /** @brief Sets interface data length to be 4-bit wide and selects
     * 1 display line and 5x10 dots character font. (DL = 0; N = 0; F = 1)
     */
    LCD_SET_FUNCTION_4_BIT_INTERFACE_ONE_DISPLAY_LINE_5X10_FONT = 0b100100,
    /** @brief Sets interface data length to be 8-bit wide and selects
     * 1 display line and 5x8 dots character font. (DL = 1; N = 1; F = 1)
     */
    LCD_SET_FUNCTION_8BIT_INTERFACE_ONE_DISPLAY_LINE_5X8_FONT = 0b110000,
    /** @brief Sets interface data length to be 8-bit wide and selects
     * 2 display lines and 5x8 dots character font. (DL = 1; N = 1; F = 0)
     */
    LCD_SET_FUNCTION_8BIT_INTERFACE_TWO_DISPLAY_LINES_5X8_FONT = 0b111000,
    /** @brief Sets interface data length to be 8-bit wide and selects
     * 1 display line and 5x10 dots character font. (DL = 1; N = 0; F = 1)
     */
    LCD_SET_FUNCTION_8BIT_INTERFACE_ONE_DISPLAY_LINE_5X10_FONT = 0b110100,
    /** @brief Sets CGRAM address. */
    LCD_SET_CGRAM_ADDRESS = 0b1000000,
    /** @brief Sets DDRAM address. */
    LCD_SET_DDRAM_ADDRESS = 0b10000000
};

/**
 * @brief This struct is used to initialize the display. It consists of three
 * instructions: *Function set*, *Display on/off control* and *Entry mode set*.
 */
typedef struct lcd_config
{
    enum lcd_instruction function;
    enum lcd_instruction on_off_control;
    enum lcd_instruction entry_mode;
} lcd_config_t;

#endif /* !__CHARACTER_LCD_COMMON_H */

/**
 * @file character_lcd.h
 * @author Iván Santiago (gh: ivanstgo)
 * @date 05/08/2025 - 19:56
 * @brief This library provides functions to configure and use a liquid crystal
 * display driven by the HD44780 chip.
 */

#ifndef _CHARACTER_LCD_H_
#define _CHARACTER_LCD_H_

#include <stdint.h>

/**
 * @brief HD44780 CGRAM address.
 */
typedef struct lcd_cgram_address
{
    /** @brief CGRAM address is 6-bit wide */
    uint8_t address : 6;
} lcd_cgram_address_t;

/**
 * @brief HD44780 DDRAM address.
 */
typedef struct lcd_ddram_address
{
    /** @brief DDRAM address is 7-bit wide */
    uint8_t address : 7;
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
    /** @brief Sets DDRAN address. */
    LCD_SET_DDRAM_ADDRESS = 0b10000000
};

/**
 * @brief HD44780 control signals and data.
 */
typedef union character_lcd
{
    uint8_t data_frame;
    struct
    {
        uint8_t register_select : 1;
        uint8_t read_write : 1;
        uint8_t enable : 1;
        uint8_t backlight : 1;
        uint8_t data : 4;
    } signals;
} character_lcd_t;

/**
 * @brief RS signal values.
 */
enum lcd_rs_signal
{
    LCD_SELECT_INSTRUCTION_REGISTER,
    LCD_SELECT_DATA_REGISTER
};

/**
 * @brief R/W signal values.
 */
enum lcd_rw_signal
{
    LCD_WRITE,
    LCD_READ
};

/**
 * @brief EN signal values.
 */
enum lcd_en_signal
{
    LCD_DISABLED,
    LCD_ENABLED
};

/**
 * @brief BL signal values.
 */
enum lcd_backlight_signal
{
    LCD_BACKLIGHT_DISABLED,
    LCD_BACKLIGHT_ENABLED
};

/**
 * @brief Configures the data length interface, display lines and character
 * font.
 * @param display pointer to a character_lcd struct.
 */
void lcd_init(character_lcd_t *display);

/**
 * @brief Sends the *clear display* instruction to the controller. The HD44780
 * chip cleans the entire display and sets the cursor position to 0.
 * @param display pointer to a character_lcd struct.
 */
void lcd_clear_display(character_lcd_t *display);

/**
 * @brief Sends the *return home* instruction to the controller. The HD44780
 * chip sets the cursor position to 0 and returns the display from being shifted
 * without changing DDRAM contents.
 * @param display pointer to a character_lcd struct.
 */
void lcd_return_home(character_lcd_t *display);

/**
 * @brief Sends an instruction to the HD44780 controller.
 * @param instruction Instruction to be written.
 * @param display pointer to a character_lcd struct.
 */
void lcd_write_instruction(character_lcd_t *display, enum lcd_instruction instruction);

/**
 * @brief Sends data to the HD44780 controller.
 * @param data Data to be written.
 * @param display pointer to a character_lcd struct.
 */
void lcd_write_data(character_lcd_t *display, uint8_t data);

/**
 * @brief Sends the "set CGRAM address" instruction to the controller.
 * @param address CGRAM address.
 * @param display pointer to a character_lcd struct.
 */
void lcd_set_cgram_address(character_lcd_t *display, lcd_cgram_address_t address);

/**
 * @brief Sends the *set DDRAM address* instruction to the controller.
 * @param address DDRAM address.
 * @param display pointer to a character_lcd struct.
 */
void lcd_set_ddram_address(character_lcd_t *display, lcd_ddram_address_t address);

/**
 * @brief Sends the *read busy flag & address* instruction to the controller.
 * @param display pointer to a character_lcd struct.
 * @return A struct that contains the busy flag status and the address counter
 * value.
 */
lcd_address_counter_t lcd_read_busy_flag_and_address(character_lcd_t *display);

#endif /* !_CHARACTER_LCD_H_ */

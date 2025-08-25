/**
 * @file character_lcd.h
 * @author Iván Santiago (gh: ivanstgo)
 * @date 05/08/2025 - 19:56
 * @brief This library provides functions to configure and use a liquid crystal
 * display driven by the HD44780 chip.
 */

#ifndef __CHARACTER_LCD_H
#define __CHARACTER_LCD_H

#include <stdint.h>
#include "character_lcd_common.h"

#if LCD_INTERFACE==I2C
#include "character_lcd_i2c.h"
#else
#include "character_lcd_parallel.h"
#endif

/**
 * @brief Configures the data length interface, display lines and character
 * font.
 * @param display pointer to a character_lcd struct.
 */
void lcd_init(character_lcd_t *display, lcd_config_t config);

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

#endif /* !__CHARACTER_LCD_H */

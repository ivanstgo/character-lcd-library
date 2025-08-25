/**
 * @file character_lcd.c
 * @author Iván Santiago (gh: ivanstgo)
 * @date 08/08/2025 - 13:33
 * @brief Character LCD library implementation file.
 */

#include "character_lcd.h"

extern void lcd_write_instruction_8bits(character_lcd_t *display,
                                   enum lcd_instruction instruction);

void lcd_init(character_lcd_t *display, lcd_config_t config)
{
#ifdef LCD_INIT_BY_INSTRUCTION
    // If HD44780 on-chip reset fails the chip can be initialized using some
    // instructions.
    uint8_t function_set = LCD_SET_FUNCTION_8BIT_INTERFACE_ONE_DISPLAY_LINE_5X8_FONT;
    LCD_WAIT_MS(50);
    lcd_write_instruction_8bits(display, function_set);
    LCD_WAIT_MS(5);
    lcd_write_instruction_8bits(display, function_set);
    LCD_WAIT_MS(1);
    lcd_write_instruction_8bits(display, function_set);
#endif /* LCD_INIT_BY_INSTRUCTION */

    // After on-chip reset the interface is 8 bits long.
    lcd_write_instruction_8bits(display, config.function);

    // Interface is 4 bits long.
    lcd_write_instruction(display, config.function);
    lcd_write_instruction(display, config.on_off_control);
    lcd_write_instruction(display, config.entry_mode);
}

void lcd_clear_display(character_lcd_t *display)
{
    lcd_write_instruction(display, LCD_CLEAR_DISPLAY);
}

void lcd_return_home(character_lcd_t *display)
{
    lcd_write_instruction(display, LCD_RETURN_HOME);
}

void lcd_set_cgram_address(character_lcd_t *display,
                           lcd_cgram_address_t address)
{
    lcd_write_instruction(display, LCD_SET_CGRAM_ADDRESS | address.value);
}

void lcd_set_ddram_address(character_lcd_t *display,
                           lcd_ddram_address_t address)
{
    lcd_write_instruction(display, LCD_SET_DDRAM_ADDRESS | address.value);
}

lcd_address_counter_t lcd_read_busy_flag_and_address(character_lcd_t *display)
{
    lcd_address_counter_t address = {.address_counter = 0, .busy_flag = 0};
    // TODO: Implement lcd_read function
    return address;
}

void lcd_put_string(character_lcd_t *display, const char *str)
{
    while (*str != 0)
    {
        lcd_write_data(display, *str);
    }
}

void lcd_set_cursor_position(character_lcd_t *display, uint8_t line,
                             uint8_t column)
{
    lcd_ddram_address_t address = {.value = column +
                                            display->line_offsets[line]};
    lcd_set_ddram_address(display, address);
}

#ifndef _LCD_PUB_H_
#define _LCD_PUB_H_

#include <stdint.h>
#include "gpiohs.h"
#include "fpioa.h"
#include "spi.h"

void tft_hard_init(uint32_t freq, bool oct);
void tft_set_clk_freq(uint32_t freq);
void tft_write_command(uint8_t cmd);
void tft_write_byte(uint8_t *data_buf, uint32_t length);
void tft_write_half(uint16_t *data_buf, uint32_t length);
void tft_write_word(uint32_t *data_buf, uint32_t length);
void tft_fill_data(uint32_t *data_buf, uint32_t length);
void tft_set_datawidth(uint8_t width);

#endif
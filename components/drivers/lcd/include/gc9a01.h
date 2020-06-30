#ifndef _GC9A01_H_
#define _GC9A01_H_

#include "lcd_pub.h"

/* clang-format off */
#define DCX_GPIONUM             (10)
#define RST_GPIONUM             (9)
#define BLK_GPIONUM             (8)

#define SPI_CHANNEL             0
#define SPI_DMA_CH				DMAC_CHANNEL1
#define LCD_SPI_SLAVE_SELECT    0
/* clang-format on */

void tft_gc9a01_init();


#endif

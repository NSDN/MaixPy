#include "global_config.h"

#if defined(CONFIG_LCD_TYPE_GC9A01)

#include "gc9a01.h"
#include "sipeed_spi.h"
#include "sleep.h"

static spi_work_mode_t standard_work_mode = SPI_WORK_MODE_0;

static void init_dcx(void)
{
    gpiohs_set_drive_mode(DCX_GPIONUM, GPIO_DM_OUTPUT);
    gpiohs_set_pin(DCX_GPIONUM, GPIO_PV_HIGH);
}

static void set_dcx_control(void)
{
    gpiohs_set_pin(DCX_GPIONUM, GPIO_PV_LOW);
}

static void set_dcx_data(void)
{
    gpiohs_set_pin(DCX_GPIONUM, GPIO_PV_HIGH);
}

static void init_rst(void)
{
    gpiohs_set_drive_mode(RST_GPIONUM, GPIO_DM_OUTPUT);
    gpiohs_set_pin(RST_GPIONUM, GPIO_PV_HIGH);
}

static void set_rst(uint8_t val)
{
    gpiohs_set_pin(RST_GPIONUM, val);
}

static void init_blk(void)
{
    gpiohs_set_drive_mode(BLK_GPIONUM, GPIO_DM_OUTPUT);
    gpiohs_set_pin(BLK_GPIONUM, GPIO_PV_HIGH);
}

static void set_blk(uint8_t val)
{
    gpiohs_set_pin(BLK_GPIONUM, val);
}

void tft_set_clk_freq(uint32_t freq)
{
    spi_set_clk_rate(SPI_CHANNEL, freq);
}

void tft_hard_init(uint32_t freq, bool oct)
{
    fpioa_set_function(29, FUNC_SPI0_SS0 + LCD_SPI_SLAVE_SELECT);
    fpioa_set_function(28, FUNC_SPI0_D0);
    fpioa_set_function(27, FUNC_SPI0_SCLK);
    fpioa_set_function(26, FUNC_GPIOHS0 + DCX_GPIONUM);
    fpioa_set_function(25, FUNC_GPIOHS0 + RST_GPIONUM);
    fpioa_set_function(24, FUNC_GPIOHS0 + BLK_GPIONUM);

    init_dcx();
    init_rst();
    init_blk();
    set_blk(0);
    set_rst(0);
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 8, 0);
    tft_set_clk_freq(freq);
    msleep(100);
    set_rst(1);
    msleep(100);
    set_blk(1);
}

void tft_write_command(uint8_t cmd)
{
    set_dcx_control();
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 8, 0);
    spi_send_data_normal_dma(SPI_DMA_CH, SPI_CHANNEL, LCD_SPI_SLAVE_SELECT, (uint8_t *)(&cmd), 1, SPI_TRANS_CHAR);
}

void tft_write_byte(uint8_t *data_buf, uint32_t length)
{
    set_dcx_data();
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 8, 0);
    spi_send_data_normal_dma(SPI_DMA_CH, SPI_CHANNEL, LCD_SPI_SLAVE_SELECT, data_buf, length, SPI_TRANS_CHAR);
}

void tft_write_half(uint16_t *data_buf, uint32_t length)
{
    set_dcx_data();
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 16, 0);
    spi_send_data_normal_dma(SPI_DMA_CH, SPI_CHANNEL, LCD_SPI_SLAVE_SELECT, data_buf, length, SPI_TRANS_SHORT);
}

void tft_write_word(uint32_t *data_buf, uint32_t length)
{
    set_dcx_data();
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 32, 0);
    spi_send_data_normal_dma(SPI_DMA_CH, SPI_CHANNEL, LCD_SPI_SLAVE_SELECT, data_buf, length, SPI_TRANS_INT);
}

void tft_fill_data(uint32_t *data_buf, uint32_t length)
{
    set_dcx_data();
    spi_init(SPI_CHANNEL, standard_work_mode, SPI_FF_STANDARD, 32, 0);
    spi_fill_data_dma(SPI_DMA_CH, SPI_CHANNEL, LCD_SPI_SLAVE_SELECT, data_buf, length);
}

void tft_set_datawidth(uint8_t width)
{

}

#define _NOP 0x00
const uint8_t tft_gc9a01_init_table[] = {
    0xEF, 0,
    0xEB, 1, 0x14,
    0xFE, 0,
    0xEF, 0,
    0xEB, 1, 0x14,
    0x84, 1, 0x40,
    0x85, 1, 0xFF,
    0x86, 1, 0xFF,
    0x87, 1, 0xFF,
    0x88, 1, 0x0A,
    0x89, 1, 0x21,
    0x8A, 1, 0x00,
    0x8B, 1, 0x80,
    0x8C, 1, 0x01,
    0x8D, 1, 0x01,
    0x8E, 1, 0xFF,
    0x8F, 1, 0xFF,
	0xB6, 2, 0x00, 0x20,
    0x36, 1, 0x08, // 0x08, 0xC8, 0x68, 0xA8
    0x3A, 1, 0x05,
    0x90, 4, 0x08, 0x08, 0x08, 0x08,
    0xBD, 1, 0x06,
    0xBC, 1, 0x00,
    0xFF, 3, 0x60, 0x01, 0x04,
    0xC3, 1, 0x13,
    0xC4, 1, 0x13,
    0xC9, 1, 0x22,
    0xBE, 1, 0x11,
    0xE1, 2, 0x10, 0x0E,
    0xDF, 3, 0x21, 0x0C, 0x02,
    0xF0, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
    0xF1, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
    0xF2, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
    0xF3, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
    0xED, 2, 0x1B, 0x0B,
    0xAE, 1, 0x77,
    0xCD, 1, 0x63,
    0x70, 9, 0x07, 0x07, 0x04, 0x0E, 0x0F, 0x09, 0x07, 0x08, 0x03,
    0xE8, 1, 0x34,
    0x62,12, 0x18, 0x0D, 0x71, 0xED, 0x70, 0x70, 0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70,
    0x63,12, 0x18, 0x11, 0x71, 0xF1, 0x70, 0x70, 0x18, 0x13, 0x71, 0xF3, 0x70, 0x70,
    0x64, 7, 0x28, 0x29, 0xF1, 0x01, 0xF1, 0x00, 0x07,
    0x66,10, 0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00,
    0x67,10, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98,
    0x74, 7, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4E, 0x00,
    0x98, 2, 0x3E, 0x07,
    0x35, 0,
    0x21, 0,
    0x11, 0,
    _NOP, 120,
    0x29, 0,
    _NOP, 20
};

void tft_gc9a01_init() {
    uint16_t i = 0, tmp = 0;
	uint8_t r = 0, len = 0;
	uint16_t size = sizeof(tft_gc9a01_init_table) / sizeof(uint8_t);
	while(i < size) {
		r = tft_gc9a01_init_table[i++];
		len = tft_gc9a01_init_table[i++];
		if(r == _NOP) {
			msleep(len);
		} else {
			tft_write_command(r);
            tft_write_byte(&tft_gc9a01_init_table[i], len); 
            i += len;
		}
    }
}
#undef _NOP

#endif

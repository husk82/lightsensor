#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stdint.h>
#include "stm32f446xx.h"
#include "I2C_Driver_H.h"

#define SSD1306_WIDTH    128
#define SSD1306_HEIGHT   64
#define SSD1306_I2C_ADDR (0x3C << 1)  // 0x3C is 7-bit addr

void SSD1306_init(I2C_TypeDef *I2Cx);
void SSD1306_clear(void);
void SSD1306_update(void);
void SSD1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void SSD1306_write_char(char ch);
void SSD1306_write_str(const char* str);

#endif
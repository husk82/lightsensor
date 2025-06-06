	#include "SSD1306_H.h"
	#include <string.h>

	static I2C_TypeDef *oled_i2c;
	static uint8_t buffer[1024]; // 128 x 64 / 8

	// Low-level I2C command
	static void SSD1306_send_command(uint8_t cmd) 
	{
	uint8_t data[2] = {0x00, cmd};
	I2C_write_bytes(oled_i2c, SSD1306_I2C_ADDR, data, 2);
	}

	// Low-level I2C data
	static void SSD1306_send_data(uint8_t* data, uint16_t size) 
	{
	for (uint16_t i = 0; i < size; i++) {
		uint8_t packet[2] = {0x40, data[i]};
		I2C_write_bytes(oled_i2c, SSD1306_I2C_ADDR, packet, 2);
	}
	}

	// Initialization sequence
	void SSD1306_init(I2C_TypeDef *I2Cx) 
	{
	oled_i2c = I2Cx;

	SSD1306_send_command(0xAE);
	SSD1306_send_command(0x20); SSD1306_send_command(0x00);
	SSD1306_send_command(0xB0);
	SSD1306_send_command(0xC8);
	SSD1306_send_command(0x00);
	SSD1306_send_command(0x10);
	SSD1306_send_command(0x40);
	SSD1306_send_command(0x81); SSD1306_send_command(0xFF);
	SSD1306_send_command(0xA1);
	SSD1306_send_command(0xA6);
	SSD1306_send_command(0xA8); SSD1306_send_command(0x3F);
	SSD1306_send_command(0xA4);
	SSD1306_send_command(0xD3); SSD1306_send_command(0x00);
	SSD1306_send_command(0xD5); SSD1306_send_command(0xF0);
	SSD1306_send_command(0xD9); SSD1306_send_command(0x22);
	SSD1306_send_command(0xDA); SSD1306_send_command(0x12);
	SSD1306_send_command(0xDB); SSD1306_send_command(0x20);
	SSD1306_send_command(0x8D); SSD1306_send_command(0x14);
	SSD1306_send_command(0xAF);

	SSD1306_clear();
	SSD1306_update();
	}

	void SSD1306_clear(void) 
	{
	memset(buffer, 0x00, sizeof(buffer));
	}

	void SSD1306_update(void) 
	{
	for (uint8_t page = 0; page < 8; page++) {
		SSD1306_send_command(0xB0 + page);
		SSD1306_send_command(0x00);
		SSD1306_send_command(0x10);
		SSD1306_send_data(&buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
	}
	}

	// Draw pixel to framebuffer
	void SSD1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color) 
	{
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;

	if (color)
		buffer[x + (y / 8) * SSD1306_WIDTH] |=  (1 << (y % 8));
	else
		buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
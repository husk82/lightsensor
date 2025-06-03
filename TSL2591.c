#include "TSL2591_H.h"

void TSL2591_write(I2C_TypeDef *I2Cx, uint8_t reg, uint8_t data) {
	uint8_t cmd = TSL2591_COMMAND_BIT | reg;
	I2C_start(I2Cx, TSL2591_ADDR, 0);
	I2C_write(I2Cx, cmd);
	I2C_write(I2Cx, data);
	I2C_stop(I2Cx);
}

uint8_t TSL2591_read(I2C_TypeDef *I2Cx, uint8_t reg) {
	uint8_t cmd = TSL2591_COMMAND_BIT | reg;
	uint8_t val;

	I2C_start(I2Cx, TSL2591_ADDR, 0);
	I2C_write(I2Cx, cmd);
	I2C_start(I2Cx, TSL2591_ADDR, 1);
	val = I2C_read_nack(I2Cx);
	I2C_stop(I2Cx);

	return val;
}

void TSL2591_init(I2C_TypeDef *I2Cx) {
	// Power on and enable ALS
	TSL2591_write(I2Cx, TSL2591_ENABLE_REG, TSL2591_ENABLE_POWERON | TSL2591_ENABLE_AEN);
	// Set integration time & gain (default: medium gain)
	TSL2591_write(I2Cx, TSL2591_CONTROL_REG, 0x20); // Medium gain, 100ms
}

uint16_t TSL2591_read_ch0(I2C_TypeDef *I2Cx) {
	uint8_t low = TSL2591_read(I2Cx, TSL2591_CH0_LOW);
	uint8_t high = TSL2591_read(I2Cx, TSL2591_CH0_HIGH);
	return (high << 8) | low;
}

uint32_t TSL2591_calculate_lux(uint16_t ch0) {
	// Simplified fake conversion (real TSL2591 needs full spectrum calc)
	return ch0 * 1.0; // You can calibrate later
}

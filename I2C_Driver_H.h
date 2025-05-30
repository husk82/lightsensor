#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "stm32f446xx.h"

#define I2C_WRITE   0
#define I2C_READ    1

void I2C_init(I2C_TypeDef *I2Cx);
void I2C_start(I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef *I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef *I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef *I2Cx);
void I2C_stop(I2C_TypeDef *I2Cx);

#endif
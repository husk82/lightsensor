#include "I2C_Driver_H.h"

void I2C1_init(void)
{
	// Enable clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	// Configure PB8 (SCL) and PB9 (SDA)
	GPIOB->MODER &= ~((3 << (8*2)) | (3 << (9*2)));  // Clear mode
	GPIOB->MODER |=  ((2 << (8*2)) | (2 << (9*2)));  // Alt func
	GPIOB->OTYPER |= (1 << 8) | (1 << 9);            // Open-drain
	GPIOB->OSPEEDR |= (3 << (8*2)) | (3 << (9*2));   // High speed
	GPIOB->PUPDR |= (1 << (8*2)) | (1 << (9*2));     // Pull-up
	GPIOB->AFR[1] |= (4 << ((8 - 8) * 4)) | (4 << ((9 - 8) * 4));  // AF4 for I2C1

	// Reset I2C1
	I2C1->CR1 |= I2C_CR1_SWRST;
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	// Set I2C clock: assuming 16 MHz APB1
	I2C1->CR2 = 16;               // APB1 = 16 MHz
	I2C1->CCR = 80;               // 100kHz standard mode
	I2C1->TRISE = 17;             // 1000ns / (1/16MHz) + 1 = 17
	I2C1->CR1 |= I2C_CR1_PE;      // Enable I2C
}

void I2C_start(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t direction)
{
	I2Cx->CR1 |= I2C_CR1_START;
	while (!(I2Cx->SR1 & I2C_SR1_SB));

	I2Cx->DR = (addr << 1) | direction;
	while (!(I2Cx->SR1 & I2C_SR1_ADDR));
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;
}

void I2C_write(I2C_TypeDef *I2Cx, uint8_t data)
{
	while (!(I2Cx->SR1 & I2C_SR1_TXE));
	I2Cx->DR = data;
	while (!(I2Cx->SR1 & I2C_SR1_BTF));
}

uint8_t I2C_read_ack(I2C_TypeDef *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_ACK;
	while (!(I2Cx->SR1 & I2C_SR1_RXNE));
	return I2Cx->DR;
}

uint8_t I2C_read_nack(I2C_TypeDef *I2Cx)
{
	I2Cx->CR1 &= ~I2C_CR1_ACK;
	I2Cx->CR1 |= I2C_CR1_STOP;
	while (!(I2Cx->SR1 & I2C_SR1_RXNE));
	return I2Cx->DR;
}

void I2C_stop(I2C_TypeDef *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_STOP;
}
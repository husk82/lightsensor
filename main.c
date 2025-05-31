#include "stm32f446xx.h"
#include "GPIO_Driver_H.h"
#include "EXTI_Driver.h"
#include "I2C_Driver_H.h"

// Global variables for LEDs 
uint8_t LED1_PIN = 10;
uint8_t LED2_PIN = 11;
uint8_t I2C_SCL_PIN = 8;
uint8_t I2C_SDA_PIN = 9;

// IRQ handler for EXTI lines 15 to 10 (includes PC13)
void EXTI15_10_IRQHandler(void)
{
	// Check if EXTI13 triggered the interrupt
	if (EXTI->PR & (1 << 13))
	{
		// Clear pending bit
		EXTI_clear_pending(13);

		// Turn off LED1
		GPIO_toggle_pin(GPIOC, LED1_PIN);

		// Turn on LED2
		GPIO_toggle_pin(GPIOC, LED2_PIN);
	}
}

int main (void)
{
	// --- Led Pin Config---
	// Configure PC10 as led1
	GPIO_config_t led1;
	led1.pin_no    = LED1_PIN;
	led1.mode      = GPIO_MODE_OUTPUT;
	led1.oType     = GPIO_OUTPUT_PP;
	led1.speed     = GPIO_SPEED_LOW;
	led1.pull      = GPIO_NO_PUPD;
	led1.altFunc   = 0;  // Not used in output mode

	GPIO_init(GPIOC, &led1);

	// Configure PC11 as led2
	GPIO_config_t led2;
	led2.pin_no    = LED2_PIN;
	led2.mode      = GPIO_MODE_OUTPUT;
	led2.oType     = GPIO_OUTPUT_PP;
	led2.speed     = GPIO_SPEED_LOW;
	led2.pull      = GPIO_NO_PUPD;
	led2.altFunc   = 0;
	
	GPIO_init(GPIOC, &led2);
	
	// Turn LEDs ON initially
  GPIO_write_pin(GPIOC, LED1_PIN, GPIO_PIN_SET);
  GPIO_write_pin(GPIOC, LED2_PIN, GPIO_PIN_SET);
	
	// --- I2C Pin Config --
	// Configure PB8 as I2C SCL
	GPIO_config_t scl;
	scl.pin_no = I2C_SCL_PIN;
	scl.mode = GPIO_MODE_ALTFN;
	scl.oType = GPIO_OUTPUT_OD;
	scl.speed = GPIO_SPEED_HIGH;
	scl.pull = GPIO_PULL_UP;
	scl.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &scl);
	
	// Configure PB9 as I2C SCL
	GPIO_config_t sda;
	sda.pin_no = I2C_SDA_PIN;
	sda.mode = GPIO_MODE_ALTFN;
	sda.oType = GPIO_OUTPUT_OD;
	sda.speed = GPIO_SPEED_HIGH;
	sda.pull = GPIO_PULL_UP;
	sda.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &sda);
	
	// Initiating I2C communication
	I2C_init(I2C1, 16000000, 100000);
	
	while(1)
	{
	}

	return 0;
}


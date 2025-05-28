#include "stm32f446xx.h"
#include "GPIO_Driver_H.h"
#include "EXTI_Driver.h"

// Global variables for LEDs 
uint8_t LED1_PIN = 10;
uint8_t LED2_PIN = 11;

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
	
	// Turn LED1 ON initially
  GPIO_write_pin(GPIOC, LED1_PIN, GPIO_PIN_SET);
  GPIO_write_pin(GPIOC, LED2_PIN, GPIO_PIN_RESET);

	// Configure PC13 as input button
	GPIO_config_t input_button;
	input_button.pin_no  = 13;
	input_button.mode    = GPIO_MODE_INPUT;
	input_button.pull    = GPIO_PULL_DOWN;	
	//input_button.oType   = GPIO_OUTPUT_PP;      // Not necessary
	//input_button.speed   = GPIO_SPEED_LOW;			// Not necessary			
	input_button.altFunc = 0;												
	
	// EXTI config for PC13
	EXTI_config_t exti;
  exti.pin_no = 13;
  exti.port_code = 2;         // GPIOC = 2
  exti.trigger_type = FALLING_EDGE;  // Trigger on button press (rising edge)
  
	EXTI_init(&exti);
	
	while(1)
	{
	}

	return 0;
}


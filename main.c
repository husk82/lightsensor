#include "stm32f446xx.h"
#include "GPIO_Driver_H.h"

int main (void)
{
	// Enable GPIOC clock
	GPIO_clock_enable(GPIOC);
	
	// Configure PC10
	GPIO_config_t led1;
	led1.pin_no = 10;
	led1.mode      = GPIO_MODE_OUTPUT;
	led1.oType     = GPIO_OUTPUT_PP;
	led1.speed     = GPIO_SPEED_LOW;
	led1.pull      = GPIO_NO_PUPD;
	led1.altFunc   = 0;  // Not used in output mode

	GPIO_init(GPIOC, &led1);

	// 3. Configure PC11
	GPIO_config_t led2;
	led2.pin_no = 11;
	led2.mode      = GPIO_MODE_OUTPUT;
	led2.oType     = GPIO_OUTPUT_PP;
	led2.speed     = GPIO_SPEED_LOW;
	led2.pull      = GPIO_NO_PUPD;
	led2.altFunc   = 0;

	GPIO_init(GPIOC, &led2);
	
	// Turn ON both leds
	GPIO_write_pin(GPIOC, 10, GPIO_PIN_SET);
	GPIO_write_pin(GPIOC, 11, GPIO_PIN_SET);
	
	return 0;
}
#include "stm32f446xx.h"
#include "GPIO_Driver_H.h"
#include "EXTI_Driver.h"
#include "I2C_Driver_H.h"
#include "TSL2591_H.h"
#include "TIM_Driver_H.h"
#include "SSD1306_H.h"

// Global variables for LEDs 
uint8_t LED1_PIN = 6;
uint8_t LED2_PIN = 7;
uint8_t I2C_SCL_PIN_LIGHT = 8;
uint8_t I2C_SDA_PIN_LIGHT = 9;
uint8_t I2C_SCL_PIN_OLED = 10;
uint8_t I2C_SDA_PIN_OLED = 3;

int main (void)
{
	// --- Led Pin Config---
	// Configure PA6 as TIM3 led1
	GPIO_config_t led1;
	led1.pin_no    = LED1_PIN;
	led1.mode      = GPIO_MODE_ALTFN;
	led1.oType     = GPIO_OUTPUT_PP;
	led1.speed     = GPIO_SPEED_LOW;
	led1.pull      = GPIO_NO_PUPD;
	led1.altFunc   = GPIO_AF2;  

	GPIO_init(GPIOA, &led1);

	// Configure PA7 as TIM3 led2
	GPIO_config_t led2;
	led2.pin_no    = LED2_PIN;
	led2.mode      = GPIO_MODE_ALTFN;
	led2.oType     = GPIO_OUTPUT_PP;
	led2.speed     = GPIO_SPEED_LOW;
	led2.pull      = GPIO_NO_PUPD;
	led2.altFunc   = GPIO_AF2;
	
	GPIO_init(GPIOA, &led2);
	
	// --- TIM Congif ---
	// Config PA6 as TIM3 Channel 1
	TIM_PWM_Config_t pwm1;
  pwm1.Instance = TIM3;
  pwm1.Prescaler = 89;        // 90 MHz / 90 = 1 MHz
  pwm1.Period = 999;          // 1 MHz / 1000 = 1 kHz PWM
  pwm1.Channel = TIM_CHANNEL_1;
	
	TIM_PWM_init(&pwm1);
	
	// Config PA7 as TIM3 Channel 2
	TIM_PWM_Config_t pwm2;
  pwm2.Instance = TIM3;
  pwm2.Prescaler = 89;        // 90 MHz / 90 = 1 MHz
  pwm2.Period = 999;          // 1 MHz / 1000 = 1 kHz PWM
  pwm2.Channel = TIM_CHANNEL_2;
	
	TIM_PWM_init(&pwm2);
	
	// --- I2C Pin Config --
	// Configure PB8 as I2C SCL
	GPIO_config_t scl_light;
	scl_light.pin_no = I2C_SCL_PIN_LIGHT;
	scl_light.mode = GPIO_MODE_ALTFN;
	scl_light.oType = GPIO_OUTPUT_OD;
	scl_light.speed = GPIO_SPEED_HIGH;
	scl_light.pull = GPIO_PULL_UP;
	scl_light.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &scl_light);
	
	// Configure PB9 as I2C SCL
	GPIO_config_t sda_light;
	sda_light.pin_no = I2C_SDA_PIN_LIGHT;
	sda_light.mode = GPIO_MODE_ALTFN;
	sda_light.oType = GPIO_OUTPUT_OD;
	sda_light.speed = GPIO_SPEED_HIGH;
	sda_light.pull = GPIO_PULL_UP;
	sda_light.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &sda_light);
	
	// Configure PB10 as I2C SCL
	GPIO_config_t scl_oled;
	scl_oled.pin_no = I2C_SCL_PIN_OLED;
	scl_oled.mode = GPIO_MODE_ALTFN;
	scl_oled.oType = GPIO_OUTPUT_OD;
	scl_oled.speed = GPIO_SPEED_HIGH;
	scl_oled.pull = GPIO_PULL_UP;
	scl_oled.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &scl_oled);
	
	// Configure PB3 as I2C SDA
	GPIO_config_t sda_oled;
	sda_oled.pin_no = I2C_SDA_PIN_OLED;
	sda_oled.mode = GPIO_MODE_ALTFN;
	sda_oled.oType = GPIO_OUTPUT_OD;
	sda_oled.speed = GPIO_SPEED_HIGH;
	sda_oled.pull = GPIO_PULL_UP;
	sda_oled.altFunc = GPIO_AF4;
	
	GPIO_init(GPIOB, &sda_oled);
	
	// Initiating I2C communication
	I2C_init(I2C1, 16000000, 100000);
	I2C_init(I2C2, 16000000, 100000);
	
	// Init sensor
	TSL2591_init(I2C1);
	
	// Init OLED
  SSD1306_init(I2C2);
	
	// Display Hello World
	SSD1306_clear();
	SSD1306_draw_string(0, 0, "Hello, World");
	SSD1306_update(I2C2);

	while (1)
	{	
		uint16_t ch0 = TSL2591_read_ch0(I2C1);
		uint32_t lux = TSL2591_calculate_lux(ch0);

		if (lux < 200) { // Day
			TIM_PWM_set_duty(&pwm1, 50);  // 5% duty cycle
			TIM_PWM_set_duty(&pwm2, 1000);  // 100% duty cycle
		} else {        // Night
			TIM_PWM_set_duty(&pwm1, 1000);  
			TIM_PWM_set_duty(&pwm2, 100);  
		}

		for (volatile int i = 0; i < 100000; ++i); // Small delay
	}

	return 0;
}


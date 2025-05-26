#ifndef GPIO_Driver_H
#define GPIO_Driver_H

#include "stm32f446xx.h"

//
// ===== GPIO MODE MACROS =====
//
#define GPIO_MODE_INPUT        0x00
#define GPIO_MODE_OUTPUT       0x01
#define GPIO_MODE_ALTFN        0x02
#define GPIO_MODE_ANALOG       0x03

//
// ===== GPIO OUTPUT TYPE =====
//
#define GPIO_OUTPUT_PP         0x00  // Push-Pull
#define GPIO_OUTPUT_OD         0x01  // Open-Drain

//
// ===== GPIO SPEED MACROS =====
//
#define GPIO_SPEED_LOW         0x00
#define GPIO_SPEED_MEDIUM      0x01
#define GPIO_SPEED_FAST        0x02
#define GPIO_SPEED_HIGH        0x03

//
// ===== GPIO PULL-UP / PULL-DOWN =====
//
#define GPIO_NO_PUPD           0x00
#define GPIO_PULL_UP           0x01
#define GPIO_PULL_DOWN         0x02

//
// ===== GPIO PIN STATE =====
//
#define GPIO_PIN_RESET         0
#define GPIO_PIN_SET           1

#endif
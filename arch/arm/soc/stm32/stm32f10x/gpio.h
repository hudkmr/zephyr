#ifndef _STM32F103_GPIO_H_
#define _STM32F103_GPIO_H_

/**
 * @brief
 *
 * Based on reference manual:
 *   STM32F101xx, STM32F102xx, STM32F103xx, STM32F105xx and STM32F107xx
 *   advanced ARM ® -based 32-bit MCUs
 *
 * Chapter 9: General-purpose and alternate-function I/Os
 *            (GPIOs and AFIOs)
 */

/* 9.2 GPIO registers */
struct stm32f10x_gpio
{
	uint32_t crl;
	uint32_t crh;
	uint32_t idr;
	uint32_t odr;
	uint32_t bsrr;
	uint32_t brr;
	uint32_t lckr;
};

#endif /* _STM32F103_GPIO_H_ */
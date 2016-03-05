/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

#include <device.h>
#include "soc.h"
#include "soc_registers.h"
#include <gpio.h>
#include <gpio/gpio_stm32.h>

/**
 * @brief map pin function to MODE register value
 */
static uint32_t __func_to_mode(int func)
{
	switch (func) {
	case STM32F10X_PIN_CONFIG_ANALOG:
	case STM32F10X_PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
	case STM32F10X_PIN_CONFIG_BIAS_PULL_UP:
	case STM32F10X_PIN_CONFIG_BIAS_PULL_DOWN:
		return 0;
	case STM32F10X_PIN_CONFIG_DRIVE_OPEN_DRAIN:
	case STM32F10X_PIN_CONFIG_DRIVE_PUSH_PULL:
	case STM32F10X_PIN_CONFIG_AF_PUSH_PULL:
	case STM32F10X_PIN_CONFIG_AF_OPEN_DRAIN:
		return 0x1;
	}
	return 0;
}

/**
 * @brief map pin function to CNF register value
 */
static uint32_t __func_to_cnf(int func)
{
	switch (func) {
	case STM32F10X_PIN_CONFIG_ANALOG:
		return 0x0;
	case STM32F10X_PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		return 0x1;
	case STM32F10X_PIN_CONFIG_BIAS_PULL_UP:
	case STM32F10X_PIN_CONFIG_BIAS_PULL_DOWN:
		return 0x2;
	case STM32F10X_PIN_CONFIG_DRIVE_PUSH_PULL:
		return 0x0;
	case STM32F10X_PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return 0x1;
	case STM32F10X_PIN_CONFIG_AF_PUSH_PULL:
		return 0x2;
	case STM32F10X_PIN_CONFIG_AF_OPEN_DRAIN:
		return 0x3;
	}
	return 0;
}

int stm32_gpio_flags_to_conf(int flags, int *pincfg)
{
	if (!pincfg)
		return DEV_FAIL;

	/* pretend we only support out direction */
	if ((flags & GPIO_DIR_MASK) == GPIO_DIR_OUT)
		*pincfg = STM32F10X_PIN_CONFIG_DRIVE_PUSH_PULL;
	else
		return DEV_NO_SUPPORT;

	return DEV_OK;
}

int stm32_gpio_configure(uint32_t *base_addr, int pin, int conf)
{
	volatile struct stm32f10x_gpio *gpio =
		(struct stm32f10x_gpio *)(base_addr);
	int cnf, mode;

	/* pins are configured in CRL (0-7) and CRH (8-15)
	 * registers
	 */
	volatile uint32_t *reg = &gpio->crl;

	if (pin > 7) {
		reg = &gpio->crh;
		pin -= 8;
	}

	/* each port is configured by 2 registers:
	 * CNFy[1:0]: Port x configuration bits
	 * MODEy[1:0]: Port x mode bits
	 *
	 * memory layout is repeated for every port:
	 *   |  CNF  |  MODE |
	 *   | [0:1] | [0:1] |
	 */
	cnf = __func_to_cnf(conf);
	mode = __func_to_mode(conf);

	/* clear bits */
	*reg &= ~(0xf << (pin * 4));
	/* set bits */
	*reg |= (cnf << (pin * 4 + 2) | mode << (pin * 4));

	return DEV_OK;
}

int stm32_gpio_set(uint32_t *base, int pin, int value)
{
	struct stm32f10x_gpio *gpio = (struct stm32f10x_gpio *)base;

	int pval = 1 << (pin & 0xf);

	if (value)
		gpio->odr |= pval;
	else
		gpio->odr &= ~pval;

	return DEV_OK;
}
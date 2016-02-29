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
 * @file SoC configuration macros for the STM32F103 family processors.
 */

#ifndef _STM32F103_SOC_H_
#define _STM32F103_SOC_H_

/* peripherals start address */
#define PERIPH_BASE           0x40000000

/* use naming consistent with STMF10x Peripherals Library */
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

/* UART */
#define USART1_ADDR           (APB2PERIPH_BASE + 0x3800)
#define USART2_ADDR           (APB1PERIPH_BASE + 0x4400)
#define USART3_ADDR           (APB1PERIPH_BASE + 0x4800)

/* Reset and Clock Control */
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)

#define GPIO_REG_SIZE         0x400
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0xC000)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)

#ifndef _ASMLANGUAGE

#include <device.h>
#include <misc/util.h>
#include <drivers/rand32.h>

/* uart configuration settings */
#define UART_IRQ_FLAGS 0

#endif /* !_ASMLANGUAGE */

#endif /* _STM32F103_SOC_H_ */

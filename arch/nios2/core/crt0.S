/*
 * Copyright (c) 2016 Intel Corporation
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

#define _ASMLANGUAGE
#include <arch/nios2/asm.h>
#include <nano_private.h>

/* exports */
GTEXT(__start)
GTEXT(__reset)

/* imports */
GTEXT(_PrepC)
GTEXT(_interrupt_stack)

	/* Allow use of r1/at (the assembler temporary register) in this
	 * code, normally reserved for internal assembler use
	 */
	.set noat

/*
 * Reset vector entry point into the system. Placed into special 'reset'
 * section so that the linker puts this at ALT_CPU_RESET_ADDR defined in
 * system.h
 *
 * This code can be at most 0x20 bytes, since the exception vector for Nios II
 * is usually configured to be 0x20 past the reset vector.
 */
SECTION_FUNC(reset, __reset)

	/* TODO initialize instruction cache, if present
	 * ZEP-275
	 */

	/* Done all we need to do here, jump to __text_start */
	movhi r1, %hi(__start)
	ori r1, r1, %lo(__start)
	jmp r1

/* Remainder of asm-land initialization code before we can jump into
 * the C domain
 */
SECTION_FUNC(TEXT, __start)

	/* TODO if shadow register sets enabled, ensure we are in set 0
	 * ZEP-258
	 */

	/* TODO initialize data cache, if present
	 * ZEP-275
	 */

#ifdef CONFIG_INIT_STACKS
	/* Pre-populate all bytes in _interrupt_stack with 0xAA */
	movhi r1, %hi(_interrupt_stack)
	ori r1, r1, %lo(_interrupt_stack)
	movhi r2, %hi(CONFIG_ISR_STACK_SIZE)
	ori r2, r2, %lo(CONFIG_ISR_STACK_SIZE)
	subi r2, r2, 3
	/* Put constant 0xaaaaaaaa in r3 */
	movhi r3, 0xaaaa
	ori r3, r3, 0xaaaa
1:
	/* Loop through the _interrupt_stack treating it as an array of
	 * uint32_t, setting each element to r3 */
	stw r3, (r1)
	subi r2, r2, 4
	addi r1, r1, 4
	blt r0, r2, 1b
#endif

	/* Set up the initial stack pointer to the interrupt stack, safe
	 * to use this as the CPU boots up with interrupts disabled and we
	 * don't turn them on until much later, when the kernel is on
	 * the main stack */
	movhi sp, %hi(_interrupt_stack)
	ori sp, sp, %lo(_interrupt_stack)
	addi sp, sp, CONFIG_ISR_STACK_SIZE
	/* Create a mask in r1 which will be used to round down sp to
	 * the desired alignment
	 */
	movi r1, STACK_ALIGN_SIZE
	subi r1, r1, 1
	nor r1, r1, r0
	/* Align the stack pointer */
	and sp, sp, r1

	/* TODO Setup the global pointer
	 * ZEP-272
	 */

	/* TODO if shadow register sets enabled, interate through them to set
	 * up. Need to clear r0, write gp, set the execption stack pointer
	 * ZEP-258
	 */

	/* Jump into C domain. _PrepC zeroes BSS, copies rw data into RAM,
	 * and then enters nanokernel _Cstart */
	call _PrepC


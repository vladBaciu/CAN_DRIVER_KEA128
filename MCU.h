/*
 * mcu.h
 *
 *  Created on: Jun 1, 2018
 *      Author: Vlad
 */

#ifndef MCU_H_
#define MCU_H_
#include "derivative.h"
#define CLKbus 20000000
#define EnableInterrupts __asm("CPSIE i")   // inline assembly IRQ EN
#define DisableInterrupts __asm("CPSID i")  // inline assembly IRQ DIS

void clks_init_FEE_40MHz(void);

void IRQs_init (IRQn_Type);


#endif /* MCU_H_ */

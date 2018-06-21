/*
 * MCU.c
 *
 *  Created on: Jun 21, 2018
 *      Author: Vlad
 */


/*
 * mcu.c
 *
 *  Created on: Jun 1, 2018
 *      Author: Vlad
 */
#include "derivative.h"
#include "mcu.h"
#include "core_cm0plus.h"


void IRQs_init (IRQn_Type IRQn) {
	NVIC_ClearPendingIRQ(IRQn);
	NVIC_EnableIRQ(IRQn);


}


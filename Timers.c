/*
 * Timers.c
 *
 *  Created on: Jun 21, 2018
 *      Author: Vlad
 */


#include "derivative.h" /* include peripheral declarations */
#include "Timers.h"
#include "PORT_Config.h" // include peripheral declarations
#include "MSCAN.h"

void TIMER_init(void) {
	SIM_SCGC |= SIM_SCGC_PIT_MASK; /* Enable bus clock to PIT module */
	PIT_MCR = 0x0; /* Turn on PIT module, Freeze disabled */


	PIT_LDVAL0 = (CLKbus/10) - 1; // PIT0: Load value to count 20M bus clocks


	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; /* Enable interrupt */
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; /* Enable (start) timer */
}

uint32_t CAN_ID_p=0x0, CAN_data1_p=0x0, CAN_data2_p=0x0, CAN_TIMESTAMP_p=0;
void PIT_CH0_IRQHandler (void) {
	MSCAN_Tx(0x7DF,8,0x02011100, 0);
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK; // Clear PIT0 flag
}

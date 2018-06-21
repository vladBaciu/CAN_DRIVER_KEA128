/*
 * main.c
 *
 *  Created on: May 15, 2018
 *      Author: Vlad
 */
#include "derivative.h"
#include "mcu.h"
#include "PORT_Config.h"
#include "Timers.h"

#include "MSCAN.h"
#include "clocks.h"
int main()
{
	DisableInterrupts; // comanda inline limbaj asamblare
	init_clks_FEE_40MHz(); //CLKbus 20

	TIMER_init();
	IRQs_init(PIT_CH0_IRQn);


	MSCAN_init();
	IRQs_init(MSCAN_RX_IRQn);
	EnableInterrupts;
	while(1)
	{

	}
	return 0;
}

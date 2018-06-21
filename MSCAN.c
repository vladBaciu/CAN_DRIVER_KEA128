/*
 * MSCAN.c
 *
 *  Created on: May 17, 2018
 *      Author: Vlad
 */
#include "derivative.h"
#include "MSCAN.h"
#include "PORT_Config.h"

void MSCAN_init()
{

	/*************************************
	 * 	Alegere pini pentru MSCAN
	 * 		CAN_TX PTC7
	 *  	CAN_RX PTC6
    **************************************/
	SIM_PINSEL1 &= ~SELECT_CAN_MASK;
	CONFIG_PIN_AS_GPIO(PORT_C,CAN_TX,OUTPUT);
	CONFIG_PIN_AS_GPIO(PORT_C,CAN_RX,INPUT);

	SIM_SCGC |= 1<<ENABLE_CAN_CLOCK;
	MSCAN_CANCTL1 |= 1<<ENABLE_CAN_BUS;   // enable can bus
	MSCAN_CANCTL0 |= CAN_INITREQUEST;  // request pentru  INIT MODE
	MSCAN_CANCTL1 |= CAN_INITAKNOWLEDGE // "Flag" sa se stie ca ca modul INIT este activ
	while ((MSCAN_CANCTL1&0x01)!=1); 	// asteapta pana se initializeaza

	/*
	 *     CONFIG MSCAN: - fiind in modul init se configureaza comunicatia CAN
	 */

	MSCAN_CANCTL1 |= 1<< SELECT_CAN_CLOCK;   // selectare bus clock, nu osc clock
	MSCAN_CANCTL1 &= ~(1<<LISTEN_MODE);      // operare in normal mode
	MSCAN_CANCTL1 |= (1<<WAKE_UP_MODE);    //activare filtru pentru a nu exista "wake up-uri" nedorite
											// filtru trece jos
	MSCAN_CANBTR0 = 0x01;                   //prescaler de 2 => 10 MHz
	MSCAN_CANBTR1=0xDC;                     //500 kbps
	MSCAN_CANIDAC = 0x10;               ///filtru


	// *** filtre  -- accepta orice frame
	MSCAN_CANIDAR0=0XFF;
	MSCAN_CANIDAR1=0XFF;
	MSCAN_CANIDAR2=0XFF;
	MSCAN_CANIDAR3=0XFF;
	MSCAN_CANIDAR4=0XFF;
	MSCAN_CANIDAR5=0XFF;
	MSCAN_CANIDAR6=0XFF;
	MSCAN_CANIDAR7=0XFF;

	MSCAN_CANIDMR0=0XFF;
	MSCAN_CANIDMR1=0XFF;
	MSCAN_CANIDMR2=0XFF;
	MSCAN_CANIDMR3=0XFF;
	MSCAN_CANIDMR4=0XFF;
	MSCAN_CANIDMR5=0XFF;
	MSCAN_CANIDMR6=0XFF;
	MSCAN_CANIDMR7=0XFF;


	MSCAN_CANCTL0 &= ~CAN_INITREQUEST;         // Disable INIT mode
	MSCAN_CANCTL1 &= ~CAN_INITAKNOWLEDGE;         // Disable INIT mode
	while ((MSCAN_CANCTL1&0x00) != 0);

	MSCAN_CANCTL0|= (1<<TIMER_ENABLE);

	MSCAN_CANRIER=0XFF;  // activeaza toate intreruperile



	while(!(MSCAN_CANCTL0 & (1<<SYNC_FLAG))); // asteapta sincronizarea
	MSCAN_CANRIER |= 0x1u;  //rx interrupt
	MSCAN_CANRFLG |= 0x1u;    //rx interrupt

}

void MSCAN_Tx(uint16_t ID,uint8_t DLC,uint32_t dataw1,uint32_t dataw0){
	uint16_t can_id=0;
	uint8_t txcanbuffer=0;
	txcanbuffer = MSCAN_CANTFLG; // flag transmitere 1=Ready;
	txcanbuffer&=0x07;
	if(txcanbuffer!=0){


		MSCAN_CANTBSEL = txcanbuffer; /* scrie valoarea in registru */
		txcanbuffer = MSCAN_CANTBSEL;

		can_id=ID>>3;
		can_id &= 0xFF;
		MSCAN_TSIDR0  = (uint8_t)can_id;   //frame id1
		can_id=ID <<5;
		can_id &= 0xFF;
		MSCAN_TEIDR1 = (uint8_t)can_id; //frameid2
		MSCAN_TSIDR1=0;
		MSCAN_TEIDR2 = 0;
		MSCAN_TEIDR3 = 0;

		MSCAN_TDLR = DLC;         //Data frame length


		MSCAN_TEDSR0 = (uint8_t) ((dataw1>>24)&0xFF);
		MSCAN_TEDSR1 = (uint8_t) ((dataw1>>16)&0xFF);
		MSCAN_TEDSR2 = (uint8_t) ((dataw1>>8)&0xFF);
		MSCAN_TEDSR3 = (uint8_t) dataw1&0xFF;
		MSCAN_TEDSR4 = (uint8_t) ((dataw0>>24)&0xFF);
		MSCAN_TEDSR5 = (uint8_t) ((dataw0>>16)&0xFF);
		MSCAN_TEDSR6 = (uint8_t) ((dataw0>>8)&0xFF);
		MSCAN_TEDSR7 = (uint8_t) dataw0&0xFF;




		switch(txcanbuffer){
			case (1):
				MSCAN_TBPR = 0x80;              // local priority
				MSCAN_CANTFLG |= 1;  // release buffer 1
				break;
			case (2):
				MSCAN_TBPR = 0x80;              // local priority
				MSCAN_CANTFLG |= 2;                // release buffer2
				break;
			case (4):
				MSCAN_TBPR = 0x80;              // local priority
				MSCAN_CANTFLG |= 4;               // release buffer3
				break;
		}
	}
	else{
		//led on
	}

void MSCAN_Rx_IRQHandler(void)
{
	uint16_t timestamp=0;
	timestamp=MSCAN_RTSRH;
	///
}
}


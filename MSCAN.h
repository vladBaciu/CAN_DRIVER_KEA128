/*
 * MSCAN.h
 *
 *  Created on: May 17, 2018
 *      Author: Vlad
 */
#ifndef MSCAN_H_
#define MSCAN_H_


/*
 *   Masti pentru inscrierea in registri
 *
 */

#define SELECT_CAN_MASK  0x10000u
#define CAN_INITREQUEST        0x1u;
#define CAN_INITAKNOWLEDGE     0x1u;

#define LISTEN_MODE         4
#define ENABLE_CAN_BUS      7
#define ENABLE_CAN_CLOCK   15
#define SELECT_CAN_CLOCK   6
#define WAKE_UP_MODE        2
#define TIMER_ENABLE         3
#define SYNC_FLAG           4

#define PORT_A  A
#define PORT_B  A
#define PORT_C  A
#define PORT_D  A

#define PORT_E	B
#define PORT_F	B
#define PORT_G	B
#define PORT_H	B



/*  PINI:
 *        RX,TX
 *
 *
 */
#define CAN_TX 23
#define CAN_RX 22



void MSCAN_init(void);
void MSCAN_Tx(uint16_t ID,uint8_t DLC,uint32_t dataw1,uint32_t dataw0 );
void MSCAN_Rx_IRQHandler(void);
#endif

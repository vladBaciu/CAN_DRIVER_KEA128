/*
 * GPIO.c
 *
 *  Created on: May 15, 2018
 *      Author: vlad
 */

#include "derivative.h"
#include "PORT_Config.h"
// led-uri pentru semnalizare
void sw_init(void){
	CONFIG_PIN_AS_GPIO(PORT_D,SW1,INPUT); /* Configure BTN0 (PTD0) as an input */
	CONFIG_PIN_AS_GPIO(PORT_D,SW2,INPUT); /* Configure BTN1 (PTD1) as an input */
	ENABLE_INPUT(PORT_D,SW1);			 /* Enable input SW1*/
	ENABLE_INPUT(PORT_D,SW2);			/*  Enable input SW2*/
	PORT_PUE0 |= 0<<SW1; // Port: No internal pullup (default)
	PORT_PUE0 |= 0<<SW2; // Port: No internal pullup (default)

}

void led_init(void){
	CONFIG_PIN_AS_GPIO(PORT_C,LED1,OUTPUT); //  LED 0 (PTC0) - output
	CONFIG_PIN_AS_GPIO(PORT_C,LED2,OUTPUT); //  LED 1 (PTC1) - output
	CONFIG_PIN_AS_GPIO(PORT_C,LED3,OUTPUT); //  LED 2 (PTC2) - output
	CONFIG_PIN_AS_GPIO(PORT_C,LED4,OUTPUT); //  LED 3 (PTC3) - output


	led_off(LED1);
	led_off(LED2);
	led_off(LED3);
	led_off(LED4);
}

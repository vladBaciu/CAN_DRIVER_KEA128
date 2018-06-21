/*
 * PORT_Config.h
 *
 *  Created on: May 15, 2018
 *      Author: Vlad
 */

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

#define CONFIG_PIN_AS_GPIO(port,register_num,mode)    XCONFIG_PIN_AS_GPIO(port,register_num,mode)
#define XCONFIG_PIN_AS_GPIO(port,register_num,mode)   (mode == 0) ? (GPIO##port##_PDDR |= 0 << register_num) : (GPIO##port##_PDDR |= 1 << register_num)

#define ENABLE_INPUT(port,register_num) 					XENABLE_INPUT(port,register_num)
#define XENABLE_INPUT(port,register_num)					GPIO##port##_PIDR ^= 1<<register_num

#define OUTPUT_SET(port,register_num)				XOUTPUT_SET(port,register_num)
#define XOUTPUT_SET(port,register_num)				GPIO##port##_PSOR |=1<<register_num
#define OUTPUT_CLEAR(port,register_num)				XOUTPUT_CLEAR(port,register_num)
#define XOUTPUT_CLEAR(port,register_num)			GPIO##port##_PCOR |=1<<register_num

#define OUTPUT_TOGGLE(port,register_num)			XOUTPUT_TOGGLE(port,register_num)
#define XOUTPUT_TOGGLE(port,register_num)			GPIO##port##_PTOR |=1<<register_num

#define CLKbus 20000000

#define LED1 16 //PTC0
#define LED2 17 //PTC1
#define LED3 18 //PTC2
#define LED4 19 //PTC3
#define SW1 24 //PTD0
#define SW2 25 //PTD1


#define led_off(led)	OUTPUT_CLEAR(PORT_A,led)
#define sw_pushed(button)	GPIOA_PDIR & (1<<button)
#define led_on(led)	OUTPUT_SET(PORT_A,led)
#define led_toggle(led)	OUTPUT_TOGGLE(PORT_A,led)


#define PORT_A  A
#define PORT_B  A
#define PORT_C  A
#define PORT_D  A

#define PORT_E	B
#define PORT_F	B
#define PORT_G	B
#define PORT_H	B

#define OUTPUT  1
#define INPUT	0

void led_init(void);
void sw_init(void);
#endif /* PORT_CONFIG_H_ */

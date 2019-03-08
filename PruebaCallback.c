#include <stdio.h>
#include <stdint.h>
#include "NVIC.h"
//#include "Bits.h"
#include "GPIO.h"
#include "RGB.h"
#include "PushButton.h"
#include "MK64F12.h"

int main2(void) {

	//Configuración de PushButtons
	PushButton_sw3_config();
	PushButton_sw2_config();

	//Configuración de RGB
	RGB_red_config();
	RGB_blue_config();
	RGB_green_config();

	/**Pin control configuration of GPIOB pin21 and pin21 as GPIO by using a special macro contained in Kinetis studio in the MK64F12. h file*/
	PORTB->PCR[21] = PORT_PCR_MUX(1);
	PORTB->PCR[22] = PORT_PCR_MUX(1);

	/**Configures GPIOB pin21 as output*/
	GPIOB->PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= 0x00400000;
	/**Configures GPIOC pin6 as input*/
	GPIOC->PDDR &= ~(0x40);

	/** Callbacks for GPIO */
	GPIO_callback_init(GPIO_B, RGB_red_on);
	GPIO_callback_init(GPIO_A, RGB_red_off);

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_4);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_4);

	NVIC_global_enable_interrupts;

	while (1) {

	}
	return 0;
}

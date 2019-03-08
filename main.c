/*
 * main.c
 *
 *  Created on: 24/02/2019
 *      Author: Lilia Lobato & Gabo Paz
 */

#include <RGB.h>
#include <GPIO.h>
#include <PushButton.h>
#include "MK64F12.h"
//#define DEBUG	//variable para debug

//Valor para el color de led encendido al iniciar
typedef enum {
	COLOR_WHITE, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE, COLOR_RED, COLOR_YELLOW
} led_color;

// función para decidir que led se enciende
void encender_led(led_color led);

int main1(void) {
	/**Variable to capture the input value*/
	uint32_t input_value_SW3 = 0;
	uint32_t input_value_SW2 = 0;
	//parámetro para el delay
	const uint32_t DELAY_ARG = 600000;

	//Configuración de PushButtons
	PushButton_sw3_config();
	PushButton_sw2_config();

	//Configuración de RGB
	RGB_red_config();
	RGB_blue_config();
	RGB_green_config();

	//Estado inicial del programa
	RGB_green_on();
	uint8_t led_status = 1;
#ifndef DEBUG
	printf("%d", led_status);
#endif

	while (1) {
		//Lectura de estado de push button
		input_value_SW3 = PushButton_read(PB_SW3);
		input_value_SW2 = PushButton_read(PB_SW2);

		//Validación de cual botón se tiene presionado ----------------------------------------------
		if (FALSE == input_value_SW3) {		//SW3
			delay(DELAY_ARG);				//Debouncer
			input_value_SW2 = PushButton_read(PB_SW2); //Valida si hay mas de un botón presionado
			if (FALSE == input_value_SW2) { //SW2
				delay(DELAY_ARG);			//Debouncer
				//si ambos sw están presionados, se enciende el color blanco
				led_status = COLOR_WHITE;
				encender_led(COLOR_WHITE);
#ifndef DEBUG
				printf("funciona\n");
#endif
			} else {//Si solo un sw está presionado
				//Verde -> Amarillo -> Rojo -> Morado -> Azul -> Verde ...
				if ((COLOR_YELLOW == led_status) | (COLOR_WHITE == led_status)) {
					//cambio de status para Led blanco y amarillo
					led_status = COLOR_GREEN;
					encender_led(COLOR_GREEN);
#ifndef DEBUG
					printf("%d\n", led_status);
#endif
				} else {
					//cambio de estatus para Led verde, morado, rojo y azul
					led_status = led_status + 1;
					encender_led(led_status);
#ifndef DEBUG
					printf("%d\n", led_status);
#endif
				}
			}
		}

		//Validación de cual botón se tiene presionado ----------------------------------------------
		if (FALSE == input_value_SW2) { 	//SW2
			delay(DELAY_ARG);				//Debouncer
			input_value_SW3 = PushButton_read(PB_SW3);	//Valida si hay mas de un botón presionado
			if (FALSE == input_value_SW3) {	//SW3
				delay(DELAY_ARG);			//Debouncer
				//si ambos sw están presionados, se enciende el color blanco
				led_status = COLOR_WHITE;
				encender_led(COLOR_WHITE);
#ifndef DEBUG
				printf("funciona\n");
#endif
			} else { //Si solo un sw está presionado
				//Verde -> Azul -> Morado -> Rojo -> Amarillo -> Verde ...
				if ((COLOR_GREEN == led_status) | (COLOR_WHITE == led_status)) {
					//cambio de status para Led blanco y verde
					led_status = COLOR_YELLOW;
					encender_led(COLOR_YELLOW);
#ifndef DEBUG
					printf("%d\n", led_status);
#endif
				} else {
					//cambio de estatus para Led morado, amarillo, rojo y azul
					led_status = led_status - 1;
					encender_led(led_status);
#ifndef DEBUG
					printf("%d\n", led_status);
#endif
				}
			}
		}
	}

	return 0;
}


/*
 * RGB.c
 *
 *  Created on: 23/02/2019
 *      Author: Lilia Lobato
 */

#include "RGB.h"
#include "MK64F12.h"
#include "GPIO.h"

gpio_pin_control_register_t RGB_input_intr_config = GPIO_MUX1;	//Configuración del GPIO

void RGB_red_config(void) {
	GPIO_clock_gating(GPIO_B);										//Activa el puerto B
	GPIO_pin_control_register(GPIO_B, RED, &RGB_input_intr_config); //Configuracion del GPIO B para el puerto del led rojo
	GPIO_write_port(GPIO_B, RED_LED);								//Escribe un valor seguro
	GPIO_data_direction_port(GPIO_B, RED_LED);						//Configura el puerto del led azul del GPIO B como Output
}
void RGB_green_config(void) {
	GPIO_clock_gating(GPIO_E);										  //Activa el puerto E
	GPIO_pin_control_register(GPIO_E, GREEN, &RGB_input_intr_config); //Configuracion del GPIO E para el puerto del led verde
	GPIO_write_port(GPIO_E, GREEN_LED);								  //Escribe un valor seguro
	GPIO_data_direction_port(GPIO_E, GREEN_LED);					  //Configura el puerto del led azul del GPIO E como Output
}
void RGB_blue_config(void) {
	GPIO_clock_gating(GPIO_B);										 //Activa el puerto B
	GPIO_pin_control_register(GPIO_B, BLUE, &RGB_input_intr_config); //Configuracion del GPIO B para el puerto del led azul
	GPIO_write_port(GPIO_B, BLUE_LED);								 //Escribe un valor seguro
	GPIO_data_direction_port(GPIO_B, BLUE_LED);						 //Configura el puerto del led azul del GPIO B como Output
}

void RGB_red_on(void) {
	GPIO_clear_pin(GPIO_B, RED);	  //enciende el led rojo
}

void RGB_red_off(void) {
	GPIO_write_port(GPIO_B, RED_LED); //apaga el led verde
}

void RGB_blue_on(void) {
	GPIO_clear_pin(GPIO_B, BLUE);	  //enciende el led azul
}

void RGB_blue_off(void) {
	GPIO_write_port(GPIO_B, BLUE_LED);//apaga el led verde
}

void RGB_green_on(void) {
	GPIO_clear_pin(GPIO_E, GREEN);	  //enciende el led verde
}

void RGB_green_off(void) {
	GPIO_write_port(GPIO_E, GREEN_LED);//apaga el led verde
}

void RGB_white_on(void) {
	//Para generar blanco se necesita un valor RGB=(255,255,255)
	RGB_green_on();
	RGB_red_on();
	RGB_blue_on();
}

void RGB_white_off(void) {
	//apaga todos los colores
	RGB_green_off();
	RGB_red_off();
	RGB_blue_off();
}

void RGB_yellow_on(void) {
	//Para generar amarillo se necesita un valor RGB=(255,255,0)
	RGB_green_on();
	RGB_red_on();
}

void RGB_yellow_off(void) {
	//Apaga color amarillo
	RGB_green_off();
	RGB_red_off();
}

void RGB_purple_on(void) {
	//Para generar morado se necesita un valor RGB=(255,0,255)
	RGB_red_on();
	RGB_blue_on();
}

void RGB_purple_off(void) {
	//Apaga color morado
	RGB_red_off();
	RGB_blue_off();
}

//genera un delay de tiempo X al ejecutar un nop n veces
void delay(uint32_t delay) {
	volatile uint32_t counter;

	for (counter = delay; counter > 0; counter--) {
		__asm("nop");
	}
}

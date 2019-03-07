/*
 * RGB.h
 *
 *  Created on: 23/02/2019
 *      Author: Lilia Lobato
 */

#ifndef RGB_H_
#define RGB_H_

#include <GPIO.h>

//Valores para encendido/apagado
#define RED_LED 	0x00400000
#define BLUE_LED 	0x00200000
#define GREEN_LED 	0x04000000
//Puertos de LED
#define RED 	22
#define BLUE 	21
#define GREEN 	26

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Estas funciones ejecutan los pasos necesarios para configurar el puerto del led correspondiente
 */
void RGB_red_config(void);
void RGB_green_config(void);
void RGB_blue_config(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Estas funciones encienden o apagan un color específico del led RGB
 */
void RGB_red_on(void);
void RGB_red_off(void);

void RGB_blue_on(void);
void RGB_blue_off(void);

void RGB_green_on(void);
void RGB_green_off(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Estas funciones encienden o apagan una serie de colores específicos del led RGB
 */
void RGB_white_on(void);
void RGB_white_off(void);

void RGB_yellow_on(void);
void RGB_yellow_off(void);

void RGB_purple_on(void);
void RGB_purple_off(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Genera un Delay de tiempo n
 */
void delay(uint32_t delay);


#endif /* RGB_H_ */

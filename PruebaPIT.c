#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RGB.h"
#include "Bits.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (1.0F)

typedef enum {
	COLOR_WHITE, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE, COLOR_RED, COLOR_YELLOW
} led_color;

int main(void) {
	uint8_t pit_inter_status = FALSE;
	RGB_red_config();
	RGB_blue_config();
	RGB_green_config();

	//Estado inicial del programa
	RGB_green_on();
	uint8_t led_status = COLOR_GREEN;

	gpio_pin_control_register_t pin_control_register_bit_d_0 = GPIO_MUX1;
	GPIO_clock_gating(GPIO_D);
	GPIO_pin_control_register(GPIO_D, bit_0, &pin_control_register_bit_d_0);
	GPIO_data_direction_pin(GPIO_D, GPIO_OUTPUT, bit_0);
	GPIO_set_pin(GPIO_D, bit_0);
	PIT_clock_gating();
	PIT_enable();

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_global_enable_interrupts;

	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);
	PIT_enable_interrupt(PIT_0);

	for (;;) {

		do {
			pit_inter_status = PIT_get_interrupt_flag_status();
		} while (FALSE == pit_inter_status);

		if (COLOR_GREEN == led_status) {
			//cambio de status para Led blanco y verde
			led_status = COLOR_YELLOW;
			encender_led(COLOR_YELLOW);
		} else {
			//cambio de estatus para Led morado, amarillo, rojo y azul
			led_status = led_status - 1;
			encender_led(led_status);
		}
			PIT_clear_interrupt_flag();

		}

		return 0;
	}

//Permite encender y apagar cada color sin importar el estado previo
	void encender_led(led_color led) {
		switch (led) {
		case COLOR_GREEN:
			RGB_white_off();
			RGB_green_on();
			break;
		case COLOR_BLUE:
			RGB_white_off();
			RGB_blue_on();
			break;
		case COLOR_PURPLE:
			RGB_white_off();
			RGB_purple_on();
			break;
		case COLOR_RED:
			RGB_white_off();
			RGB_red_on();
			break;
		case COLOR_YELLOW:
			RGB_white_off();
			RGB_yellow_on();
			break;
		case COLOR_WHITE:
			RGB_white_off();
			RGB_white_on();
			break;
		default:
			break;
		}

	}


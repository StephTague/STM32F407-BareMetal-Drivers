/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        002led_button.c
 * Author:      Lauris Taguetieu
 * Board:       STM32F407G-DISC1
 * Target MCU:  STM32F407VGT6
 * Core:        Arm Cortex-M4 with FPU
 * Description: Application example demonstrating GPIO input and output.
 *              The user button on PA0 is used to toggle the green LED
 *              connected to PD12.
 * Date:        17.08.2026
 ******************************************************************************/

#include <stdint.h>
#include "STM32F407xx.h"
#include "drv_gpio.h"

void delay (void)
{
	for (volatile uint32_t i = 0; i < 500000 ; i++);
}

int main (void)
{
	GPIO_Handle_t GpioLed, GpioBtn;

 /*
	     * Configure PD12.
	     * On the STM32F407G-DISC1 board, PD12 is connected to the green user LED.
*/
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;


	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT; //Configure PD12 as a general-purpose output
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
	GpioLed.GPIO_PinConfig.GPIO_PinOutputType = GPIO_OP_TYPE_PP ;//Configure the output driver as push-pull
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ; // Disable internal pull-up and pull-down resistors

	  /*
	     * Enable the peripheral clock for GPIOD before accessing
	     * the GPIOD configuration registers.
	     */
	GPIO_PeriClockControl(GPIOD,ENABLE);

	/* Initialize PD12 using the configuration stored in GpioLed */
	GPIO_Init(&GpioLed);


	 /*
		     * Configure PA0.
		     * On the STM32F407G-DISC1 board, PA0 is connected to the user Push Button.
	*/
		GpioLed.pGPIOx = GPIOA;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;


		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN; //Configure PA0 as a general-purpose input
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ; // Disable internal pull-up and pull-down resistors

		  /*
		     * Enable the peripheral clock for GPIOA before accessing
		     * the GPIOA configuration registers.
		     */
		GPIO_PeriClockControl(GPIOA,ENABLE);

		/* Apply the button configuration to the GPIO hardware registers */
		GPIO_Init(&GpioBtn);

	while(1)
	{
		if( GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0))
		{
			delay();
			/*
					         * Toggle the output state of PD12:
					         * HIGH -> LOW -> HIGH -> ...
					         */
					GPIO_TogglePin(GPIOD, GPIO_PIN_NO_12);

				/* Wait before toggling the LED again */
		}

	}

	return 0;

}

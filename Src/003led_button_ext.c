/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        002led_button_ext.c
 * Author:      Lauris Taguetieu
 * Board:       STM32F407G-DISC1
 * Target MCU:  STM32F407VGT6
 * Core:        Arm Cortex-M4 with FPU
 * Description: Application example demonstrating GPIO input and output.
 *              An external push button connected to PB12 controls an external
 *              LED connected to PA14. The button input uses the internal
 *              pull-up resistor and is therefore active-low.
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
	 * LED CONFIGURATION
     * The external LED is connected to PA14.
*/
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;


	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT; //Configure PA14 as a general-purpose output
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
	GpioLed.GPIO_PinConfig.GPIO_PinOutputType = GPIO_OP_TYPE_PP ;//Configure the output driver as push-pull
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ; // Disable internal pull-up and pull-down resistors

	  /*
	     * Enable the peripheral clock for GPIOA before accessing
	     * the GPIOA configuration registers.
	     */
	GPIO_PeriClockControl(GPIOA,ENABLE);

	/* Initialize PA14 using the configuration stored in GpioLed */
	GPIO_Init(&GpioLed);


	 /*
		     * Configure PB12.
		     * PB12 is connected to the external Push Button.
	*/
		GpioLed.pGPIOx = GPIOB;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;


		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN; //Configure PB12 as a general-purpose input
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU ; // internal pull-up resistors

		  /*
		     * Enable the peripheral clock for GPIOB before accessing
		     * the GPIOB configuration registers.
		     */
		GPIO_PeriClockControl(GPIOB,ENABLE);

		/* Apply the button configuration to the GPIO hardware registers */
		GPIO_Init(&GpioBtn);

	while(1)
	{
		if( GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == 0U)
		{
			 /* Small software delay to reduce mechanical button bouncing */
			delay();
			/*
					         * Toggle the output state of PA14:
					         * HIGH -> LOW -> HIGH -> ...
					         */
					GPIO_TogglePin(GPIOA, GPIO_PIN_NO_14);

		}
		else
		{

			/* When the button is released, force the LED output LOW.*/

			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_14, GPIO_PIN_RESET);
		}

	}

	return 0;

}

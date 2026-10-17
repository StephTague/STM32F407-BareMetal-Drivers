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
#include <stdio.h>
#include <string.h>
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
	memset(&GpioLed,0, sizeof(GpioLed));
	memset(&GpioLed,0, sizeof(GpioBtn));

 /*
	 * LED CONFIGURATION
     * The external LED is connected to PD12.
*/
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;


	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT; //Configure PA14 as a general-purpose output
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
	GpioLed.GPIO_PinConfig.GPIO_PinOutputType = GPIO_OP_TYPE_PP ;//Configure the output driver as push-pull
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ; // Disable internal pull-up and pull-down resistors

	  /*
	     * Enable the peripheral clock for GPIOA before accessing
	     * the GPIOA configuration registers.
	     */
	GPIO_PeriClockControl(GPIOD,ENABLE);

	/* Initialize PA14 using the configuration stored in GpioLed */
	GPIO_Init(&GpioLed);


	 /*
		     * Configure PD5.
		     * PD5 is connected to the external Push Button.
	*/
		GpioLed.pGPIOx = GPIOD;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;


		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT; //Configure PD5 as a interrupt falling edge
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HIGH ; // Configure the output speed
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU ; // internal pull-up resistors


		/* Apply the button configuration to the GPIO hardware registers */
		GPIO_Init(&GpioBtn);

		/* IRQ Configurations*/
		GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIO_15);
		GPIO_IRQConfig(IRQ_NO_EXTI9_5, ENABLE);
		while(1);

}


void EXTI9_5_IRQHandler (void)
	{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_TogglePin( GPIOD, GPIO_PIN_NO_12);

	}

/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        drv_gpio.c
 * Author:      Lauris Taguetieu
 * Board:       STM32F407G-DISC1
 * Target MCU:  STM32F407VGT6
 * Core:        Arm Cortex-M4 with FPU
 * Description: Implementation of the GPIO driver APIs, including peripheral
 *              clock control, pin configuration, and GPIO data operations.
 * Date:        31.07.2026
 ******************************************************************************/

#include <stdint.h>
#include "STM32F407xx.h"
#include "drv_gpio.h"

/******************************************************************************
 * @fn         - GPIO_PeriClockControl
 *
 * @brief      - Enables or disables the peripheral clock of a GPIO port.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral whose clock must be
 *                       controlled.
 * @param[in]  - EnOrDi: ENABLE to activate the peripheral clock or DISABLE
 *                       to deactivate it.
 *
 * @return     - None
 *
 * @note       - The current implementation supports GPIOA, GPIOB, GPIOC,
 *               and GPIOD. An invalid GPIO pointer or control value is ignored.
 ******************************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
		}
		else if (pGPIOx == GPIOB)
		{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_Msk;
		}
		else if (pGPIOx == GPIOC)
		{
		   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;
		}
		else if (pGPIOx == GPIOD)
		{
		   RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN_Msk;
		}
    }
	else if (EnorDi == DISABLE)
	{
		if(pGPIOx == GPIOA)
		{
		  RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN_Msk;
		}
		else if (pGPIOx == GPIOB)
		{
		  RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN_Msk;
		}
		else if (pGPIOx == GPIOC)
		{
		  RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN_Msk;
		}
		else if (pGPIOx == GPIOD)
		{
		 RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN_Msk;
		}
	}
}


/******************************************************************************
 * @fn         - GPIO_Init
 *
 * @brief      - Initializes a GPIO pin according to the configuration stored
 *               in the supplied GPIO handle.
 *
 * @param[in]  - pGPIOHandle: Pointer to a GPIO handle containing the target
 *                            GPIO port and pin configuration settings.
 *
 * @return     - None
 *
 * @note       - The GPIO peripheral clock must be enabled before accessing
 *               the GPIO registers. Interrupt modes require additional EXTI
 *               and SYSCFG configuration.
 ******************************************************************************/

void GPIO_Init(const GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0U; //temp.register
	//1. configure the mode of the gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
	 // the non interrupt mode /* Clear the current two-bit mode field */
     pGPIOHandle->pGPIOx->MODER &= ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	 temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	 pGPIOHandle->pGPIOx->MODER |= temp;
	}
	else
	{
		//Interrupt mode
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// configure the FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

			// Clear the RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// configure the RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// Clear the FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// configure both FTSR & RTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		/* Configure the GPIO port selection in the corresponding SYSCFG_EXTICR register */

		/* Select which EXTICR register contains the configuration for this EXTI line.
		 * Pins 0-3   -> EXTICR[0]
		 * Pins 4-7   -> EXTICR[1]
		 * Pins 8-11  -> EXTICR[2]
		 * Pins 12-15 -> EXTICR[3]
		 */
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4u;

		/* Select the 4-bit field inside the selected EXTICR register */
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4u;

		/* Convert the GPIO peripheral base address into the SYSCFG port code */
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

		/* Enable the SYSCFG peripheral clock before accessing its registers */
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;

		/* Make sure that the GPIO port code is valid */
		if (portCode != 0xFFU)
		{
		    /* Clear the previous 4-bit GPIO port selection */
		    SYSCFG->EXTICR[temp1] &= ~(0xFU << (temp2 * 4U));

		    /* Write the new GPIO port code into the selected 4-bit field */
		    SYSCFG->EXTICR[temp1] |= ((uint32_t)portCode << (temp2 * 4U));
		}

		//  enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	//2. configure the speed of the gpio pin
	temp = 0U;
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	//3. configure the pupd settings of the gpio pin
	temp = 0U;
	pGPIOHandle->pGPIOx->PUPDR &=  ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	//4. configure the optype of the gpio pin
	temp = 0U;
	pGPIOHandle->pGPIOx->OTYPER &= ~(1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinOutputType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

		//5. configure the altfn of the gpio pin
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	    {
	        uint32_t position = 4U * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8U);

	        temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunction << position);

	        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber < 8U)
	        {
	            /* Pins 0 to 7 use AFRL */
	            pGPIOHandle->pGPIOx->AFRL &= ~(0xFU << position);
	            pGPIOHandle->pGPIOx->AFRL |= temp;
	        }
	        else
	        {
	            /* Pins 8 to 15 use AFRH */
	            pGPIOHandle->pGPIOx->AFRH &= ~(0xFU << position);
	            pGPIOHandle->pGPIOx->AFRH |= temp;
	        }
	    }

}

/******************************************************************************
 * @fn         - GPIO_DeInit
 *
 * @brief      - Resets all registers of the selected GPIO peripheral to their
 *               reset values.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral to be reset.
 *
 * @return     - None
 *
 * @note       - The reset is performed by asserting and then releasing the
 *               corresponding bit in the RCC AHB1 peripheral reset register.
 *               The current implementation supports GPIOA to GPIOD.
 ******************************************************************************/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
			{
				RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST_Msk;
				RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOARST_Msk;
			}
	else if (pGPIOx == GPIOB)
			{
				RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOBRST_Msk;
				RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOBRST_Msk;
			}
	else if (pGPIOx == GPIOC)
			{
			   RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOCRST_Msk;
			   RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOCRST_Msk;
			}
	else if (pGPIOx == GPIOD)
			{
			   RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIODRST_Msk;
			   RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIODRST_Msk;
			}
}


/******************************************************************************
 * @fn         - GPIO_ReadFromInputPin
 *
 * @brief      - Reads the input state of a selected GPIO pin.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral.
 * @param[in]  - pinNumber: GPIO pin number to read, from 0 to 15.
 *
 * @return     - 1U when the input pin is high.
 *               0U when the input pin is low.
 *
 * @note       - The selected pin should be configured as an input or as an
 *               alternate-function input before calling this function.
 ******************************************************************************/

uint8_t GPIO_ReadFromInputPin(const GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    uint8_t value = 0U;
    value = (uint8_t)((pGPIOx->IDR >> pinNumber) & 0x1U);
    return value;
}

/******************************************************************************
 * @fn         - GPIO_ReadFromInputPort
 *
 * @brief      - Reads the input states of all pins of a GPIO port.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral.
 *
 * @return     - A 16-bit value representing the input states of GPIO pins
 *               0 to 15. A set bit indicates a high input level, while a
 *               cleared bit indicates a low input level.
 *
 * @note       - Bit 0 represents pin 0, bit 1 represents pin 1, and so on
 *               through bit 15.
 ******************************************************************************/

uint16_t GPIO_ReadFromInputPort(const GPIO_RegDef_t *pGPIOx)
{
	uint16_t value = 0U;
	value = (uint16_t)(pGPIOx->IDR );
	return value;
}

/******************************************************************************
 * @fn         - GPIO_WriteToOutputPin
 *
 * @brief      - Sets or resets the output state of a selected GPIO pin.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral.
 * @param[in]  - pinNumber: GPIO pin number to modify, from 0 to 15.
 * @param[in]  - value: GPIO_PIN_SET to drive the pin high or GPIO_PIN_RESET
 *                      to drive the pin low.
 *
 * @return     - None
 *
 * @note       - The selected pin should be configured in output mode before
 *               calling this function. Invalid values are ignored.
 ******************************************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value)
{
	if (value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1U << pinNumber);// write 1 to the output data register at the bit field corresponding to the pin number
	}
	else if (value == GPIO_PIN_RESET)
	{
		pGPIOx->ODR &= ~(1U << pinNumber);	// write 0
	}
}

/******************************************************************************
 * @fn         - GPIO_WriteToOutputPort
 *
 * @brief      - Writes a 16-bit value to all output pins of a GPIO port.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral.
 * @param[in]  - value: 16-bit value to write to the GPIO output data register.
 *
 * @return     - None
 *
 * @note       - Each bit of value controls the corresponding GPIO pin:
 *               bit 0 controls pin 0, bit 1 controls pin 1, and so on.
 *               This operation overwrites the output state of all 16 pins.
 ******************************************************************************/

void GPIO_WriteTOOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = (uint32_t)value;
}

/******************************************************************************
 * @fn         - GPIO_ToggleOutputPin
 *
 * @brief      - Toggles the output state of a selected GPIO pin.
 *
 * @param[in]  - pGPIOx: Pointer to the GPIO peripheral.
 * @param[in]  - pinNumber: GPIO pin number to toggle, from 0 to 15.
 *
 * @return     - None
 *
 * @note       - The selected pin should be configured in output mode before
 *               calling this function. This function modifies ODR using a
 *               read-modify-write operation.
 ******************************************************************************/

void GPIO_TogglePin( GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
	pGPIOx->ODR ^= (1U << pinNumber);
}

/******************************************************************************
 * @fn         - GPIO_IRQConfig
 *
 * @brief      - Enables or disables an interrupt request in the NVIC.
 *
 * @param[in]  - IRQNumber: NVIC IRQ number to configure.
 * @param[in]  - EnorDi: ENABLE to enable the interrupt or DISABLE to disable it.
 *
 * @return     - None
 *
 * @note       - ISER0/ICER0 control IRQ 0-31,
 *               ISER1/ICER1 control IRQ 32-63,
 *               ISER2/ICER2 control IRQ 64-81 on STM32F407.
 ******************************************************************************/

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	// to code later
	if(EnorDi == ENABLE)
	{
		if (IRQNumber <= 31u)
		{
			/* Program ISER0 register: IRQ 0-31 */
			*NVIC_ISER0 |= (1u << IRQNumber) ;
		}
	    else if (IRQNumber > 31u && IRQNumber < 64u)
		{
	    	/* Program ISER1 register: IRQ 32-63 */
	    	*NVIC_ISER1 |= (1u << (IRQNumber % 32u)) ;
		}
		else if (IRQNumber >= 64u && IRQNumber < 96u)
		{
			/* Program ISER2 register: IRQ 64-81 */
			*NVIC_ISER2 |= (1u << (IRQNumber % 64u)) ;
		}
	}
	else
	{
	   if (IRQNumber <= 31u)
		{
		   /* Program ICER0 register: IRQ 0-31 */
		   *NVIC_ICER0 = (1u << IRQNumber) ;
		}
	 else if (IRQNumber > 31u && IRQNumber < 64u)
		{
		 /* Program ICER1 register: IRQ 32-63 */
		 *NVIC_ICER1 = (1u << (IRQNumber % 32u)) ;
		}
	else if (IRQNumber >= 64u && IRQNumber < 96u)
	    {
		 /* Program ICER2 register: IRQ 64-81 */
		*NVIC_ICER2 = (1u << (IRQNumber % 64u)) ;
	    }
	}
}

/******************************************************************************
 * @fn         - GPIO_IRQPriorityConfig
 *
 * @brief      - Configures the priority of a selected interrupt request
 *               in the NVIC interrupt priority registers.
 *
 * @param[in]  - IRQNumber: NVIC interrupt request number whose priority
 *                          must be configured.
 * @param[in]  - IRQPriority: Priority level to assign to the interrupt.
 *                            Valid values for STM32F407 are 0U to 15U.
 *
 * @return     - None
 *
 * @note       - Each NVIC IPR register contains four 8-bit priority fields.
 *               The STM32F407 implements 4 priority bits, located in the
 *               upper four bits of each 8-bit priority field.
 *               Lower numerical values represent higher interrupt priority.
 ******************************************************************************/

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	/* Find the IPR register that contains the selected IRQ priority field */
	uint8_t iprx = IRQNumber / 4u;

	/* Find the position of the IRQ priority field inside the selected IPR */
	uint8_t iprx_section = IRQNumber % 4u;

	/* Calculate the bit position of the implemented priority bits */
	uint8_t shift_amount = (8u * iprx_section) + (8u - NVIC_PR_BITS_IMPLEMENTED);

	/* Clear the previous priority value */
	NVIC_IPR[iprx] &= ~(0xFU << shift_amount);

	/* Write the new priority value */
	NVIC_IPR[iprx] |= (IRQPriority << shift_amount);

}


void GPIO_IRQHandling(uint8_t PinNumber)
{
	/* Clear the EXTI PR register */
	if (EXTI->PR & (1 << PinNumber ))
	{
		EXTI->PR = (1 << PinNumber);
	}
}

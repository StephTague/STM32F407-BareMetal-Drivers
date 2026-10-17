/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        drv_gpio.h
 * Author:      Lauris Taguetieu
 * Board:       STM32F407G-DISC1
 * Target MCU:  STM32F407VGT6
 * Description: Public definitions and APIs for the GPIO driver.
 * Date:        31.07.2026
 ******************************************************************************/

#ifndef INC_DRV_GPIO_H_
#define INC_DRV_GPIO_H_
#include <stdint.h>
#include "STM32F407xx.h"

/*******************************************************************************
 * GPIO pin configuration structure
 ******************************************************************************/

typedef struct
{
    uint8_t GPIO_PinNumber; // Possible values from  @GPIO_PIN_NUMBERS
    uint8_t GPIO_PinMode; // possible values from @GPIO_PIN_MODES
    uint8_t GPIO_PinSpeed; // Possible values from @GPIO_PIN_OP_SPEEDS
    uint8_t GPIO_PinPuPdControl; // Possible values from @GPIO_PIN_PUPD
    uint8_t GPIO_PinOutputType; // Possible values from  @GPIO_PIN_OP_TYPES
    uint8_t GPIO_PinAltFunction;

} GPIO_PinConfig_t;

/*******************************************************************************
 * GPIO handle structure
 ******************************************************************************/

typedef struct
{
    GPIO_RegDef_t    *pGPIOx;        /* GPIO port base-address pointer */
    GPIO_PinConfig_t GPIO_PinConfig; /* GPIO pin configuration settings */

} GPIO_Handle_t;

/*******************************************************************************
 * GPIO pin numbers. @GPIO_PIN_NUMBERS
 ******************************************************************************/
#define GPIO_PIN_NO_0                  0u
#define GPIO_PIN_NO_1                  1u
#define GPIO_PIN_NO_2                  2u
#define GPIO_PIN_NO_3                  3u
#define GPIO_PIN_NO_4                  4u
#define GPIO_PIN_NO_5                  5u
#define GPIO_PIN_NO_6                  6u
#define GPIO_PIN_NO_7                  7u
#define GPIO_PIN_NO_8                  8u
#define GPIO_PIN_NO_9                  9u
#define GPIO_PIN_NO_10                 10u
#define GPIO_PIN_NO_11                 11u
#define GPIO_PIN_NO_12                 12u
#define GPIO_PIN_NO_13                 13u
#define GPIO_PIN_NO_14                 14u
#define GPIO_PIN_NO_15                 15u

/*******************************************************************************
 * GPIO pin possible modes. @GPIO_PIN_MODES
 ******************************************************************************/
#define GPIO_MODE_IN                  0u // Input mode
#define GPIO_MODE_OUT                  1u // Output mode
#define GPIO_MODE_ALTFN               2u // Alternate function mode
#define GPIO_MODE_ANALOG              3u // Analog mode

/* Driver-level interrupt modes; not direct MODER register values. */
#define GPIO_MODE_IT_FT               4u // Interrupt falling edge trigger
#define GPIO_MODE_IT_RT               5u // Interrupt rising edge trigger
#define GPIO_MODE_IT_RFT              6u // Interrupt rising & falling edge trigger

/*******************************************************************************
 * GPIO pin possible output types. @GPIO_PIN_OP_TYPES
 ******************************************************************************/
#define GPIO_OP_TYPE_PP               0u // Output PushPull
#define GPIO_OP_TYPE_OD               1u // Output Open Drain

/*******************************************************************************
 * GPIO pin possible output speeds. @GPIO_PIN_OP_SPEEDS
 ******************************************************************************/
#define GPIO_OP_SPEED_LOW             0u // Low speed
#define GPIO_OP_SPEED_MEDIUM          1u // Medium speed
#define GPIO_OP_SPEED_HIGH            2u // High Speed
#define GPIO_OP_SPEED_VHIGH           3u // Very High speed

/*******************************************************************************
 * GPIO pin possible pull up/down options. @GPIO_PIN_PUPD
 ******************************************************************************/
#define GPIO_NO_PUPD                  0u // No Pull Up Pull Down
#define GPIO_PIN_PU                   1u // Pull Up
#define GPIO_PIN_PD                   2u // Pull Down

/*******************************************************************************
 * GPIO alternate-function numbers
 ******************************************************************************/

#define GPIO_AF0_SYSTEM              0U
#define GPIO_AF4_I2C                 4U
#define GPIO_AF5_SPI                 5U
#define GPIO_AF7_USART               7U

/*******************************************************************************
 *  GPIO driver APIs
 ******************************************************************************/
//Peripheral clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//Initialization and  De-Initialization
void GPIO_Init(const GPIO_Handle_t *pGPIOHandle);
void GPIO_Deinit(GPIO_RegDef_t *pGPIOx);

//Data read and write
uint8_t GPIO_ReadFromInputPin(const GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
uint16_t GPIO_ReadFromInputPort(const GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value);
void GPIO_WriteTOOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_TogglePin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//IRQ configuration and ISR handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void  GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_DRV_GPIO_H_ */

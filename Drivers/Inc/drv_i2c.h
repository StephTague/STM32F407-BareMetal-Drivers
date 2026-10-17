/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        drv_i2c.h
 * Author:      Lauris Taguetieu
 * Board:       STM32F407G-DISC1
 * Target MCU:  STM32F407VGT6
 * Description: Public definitions, configuration structures and APIs for
 *              the I2C driver.
 * Date:        19.08.2026
 ******************************************************************************/

#ifndef INC_DRV_I2C_H_
#define INC_DRV_I2C_H_

#include <stdint.h>
#include "STM32F407xx.h"

/*******************************************************************************
 * I2C configuration structure
 ******************************************************************************/

typedef struct
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_ACKControl;
    uint8_t  I2C_FMDutyCycle;

} I2C_Config_t;

/*******************************************************************************
 * I2C handle structure
 ******************************************************************************/

typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;

} I2C_Handle_t;

/*******************************************************************************
 * I2C serial clock speeds. @I2C_SCL_SPEEDS
 ******************************************************************************/

#define I2C_SCL_SPEED_SM             100000U
#define I2C_SCL_SPEED_FM200K           200000U
#define I2C_SCL_SPEED_FM             400000U

/*******************************************************************************
 * I2C acknowledge control. @I2C_ACK_CONTROL
 ******************************************************************************/

#define I2C_ACK_DISABLE              0U
#define I2C_ACK_ENABLE               1U

/*******************************************************************************
 * I2C Fast-mode duty cycle. @I2C_FM_DUTY
 ******************************************************************************/

#define I2C_FM_DUTY_2               0U
#define I2C_FM_DUTY_16_9            1U

/*******************************************************************************
 * I2C repeated-start control
 ******************************************************************************/

#define I2C_DISABLE_SR               0U
#define I2C_ENABLE_SR                1U

/*******************************************************************************
 * I2C driver APIs
 ******************************************************************************/

/* Peripheral clock control */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/* Initialization and de-initialization */
void I2C_Init(const I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/* Data transmission and reception */
void I2C_MasterSendData(...);
void I2C_MasterReceiveData(...);

/* IRQ configuration */
void I2C_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

#endif /* INC_DRV_I2C_H_ */

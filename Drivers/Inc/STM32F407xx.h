/******************************************************************************
 * Project:     STM32F407 Bare-Metal Driver Library
 * File:        STM32F407xx.h
 * Author:      Lauris Taguetieu
 * Target MCU:  STM32F407VGT6
 * Core:        ARM Cortex-M4 with FPU
 * Description: Device-specific definitions, including memory addresses,
 *              peripheral base addresses, register offsets, and bit fields.
 * Date:        30.07.2026
 ******************************************************************************/

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

/*******************************************************************************
 * NVIC Interrupt Set-Enable Register addresses
 *
 * Each 32-bit ISER register controls 32 interrupt request channels.
 *
 * ISER0 -> IRQ 0  to IRQ 31
 * ISER1 -> IRQ 32 to IRQ 63
 * ISER2 -> IRQ 64 to IRQ 81 used by STM32F407
 ******************************************************************************/

#define NVIC_ISER0_BASEADDR          0xE000E100UL
#define NVIC_ISER1_BASEADDR          0xE000E104UL
#define NVIC_ISER2_BASEADDR          0xE000E108UL


/*******************************************************************************
 * NVIC Interrupt Clear-Enable Register addresses
 *
 * Each 32-bit ICER register controls 32 interrupt request channels.
 *
 * ICER0 -> IRQ 0  to IRQ 31
 * ICER1 -> IRQ 32 to IRQ 63
 * ICER2 -> IRQ 64 to IRQ 81 used by STM32F407
 ******************************************************************************/

#define NVIC_ICER0_BASEADDR          0xE000E180UL
#define NVIC_ICER1_BASEADDR          0xE000E184UL
#define NVIC_ICER2_BASEADDR          0xE000E188UL

/*******************************************************************************
 * NVIC Interrupt Set-Enable Register definitions
 ******************************************************************************/

#define NVIC_ISER0    ((volatile uint32_t *)NVIC_ISER0_BASEADDR)
#define NVIC_ISER1    ((volatile uint32_t *)NVIC_ISER1_BASEADDR)
#define NVIC_ISER2    ((volatile uint32_t *)NVIC_ISER2_BASEADDR)


/*******************************************************************************
 * NVIC Interrupt Clear-Enable Register definitions
 ******************************************************************************/

#define NVIC_ICER0    ((volatile uint32_t *)NVIC_ICER0_BASEADDR)
#define NVIC_ICER1    ((volatile uint32_t *)NVIC_ICER1_BASEADDR)
#define NVIC_ICER2    ((volatile uint32_t *)NVIC_ICER2_BASEADDR)

/*******************************************************************************
 * NVIC Interrupt Priority Register configuration
 *
 * Each 32-bit priority register contains four 8-bit priority fields:
 *
 * IPR0 -> IRQ0  to IRQ3
 * IPR1 -> IRQ4  to IRQ7
 * IPR2 -> IRQ8  to IRQ11
 * ...
 *
 * The STM32F407 implements 4 priority bits out of each 8-bit priority field,
 * providing 16 programmable priority levels from 0 to 15.
 *
 * Priority 0  -> highest priority
 * Priority 15 -> lowest priority
 ******************************************************************************/

#define NVIC_IPR_BASEADDR               0xE000E400UL
#define NVIC_IPR                   ((volatile uint32_t *)NVIC_IPR_BASEADDR)

#define NVIC_PR_BITS_IMPLEMENTED        4U

/*******************************************************************************
 * Memory base addresses
 ******************************************************************************/

#define FLASH_BASEADDR                   0x08000000UL
#define SRAM1_BASEADDR                   0x20000000UL // also the base address of SRAM
#define SRAM2_BASEADDR                   0x2001C000UL
#define SYS_MEMORY_BASEADDR              0x1FFF0000UL //System memory

/*******************************************************************************
 * Peripheral bus base addresses
 ******************************************************************************/

#define AHB1_BASEADDR                   0x40020000UL
#define AHB2_BASEADDR                   0x50000000UL
#define AHB3_BASEADDR                   0xA0000000UL
#define APB1_BASEADDR                   0x40000000UL
#define PERIPH_BASEADDR                 APB1_BASEADDR
#define APB2_BASEADDR                   0x40010000UL

/*******************************************************************************
 * AHB1 peripheral base addresses
 ******************************************************************************/

#define GPIOA_BASEADDR                 (AHB1_BASEADDR + 0x0000UL)
#define GPIOB_BASEADDR                 (AHB1_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR                 (AHB1_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR                 (AHB1_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR                 (AHB1_BASEADDR + 0x1000UL)
#define GPIOF_BASEADDR                 (AHB1_BASEADDR + 0x1400UL)
#define GPIOG_BASEADDR                 (AHB1_BASEADDR + 0x1800UL)
#define GPIOH_BASEADDR                 (AHB1_BASEADDR + 0x1C00UL)
#define GPIOI_BASEADDR                 (AHB1_BASEADDR + 0x2000UL)

#define RCC_BASEADDR                   (AHB1_BASEADDR + 0x3800UL)

/*******************************************************************************
 * APB1 peripheral base addresses
 ******************************************************************************/

#define TIM2_BASEADDR                  (APB1_BASEADDR + 0x0000UL)
#define SPI2_BASEADDR                  (APB1_BASEADDR + 0x3800UL)
#define USART2_BASEADDR                (APB1_BASEADDR + 0x4400UL)
#define UART4_BASEADDR                 (APB1_BASEADDR + 0x4C00UL)
#define I2C1_BASEADDR                  (APB1_BASEADDR + 0x5400UL)
#define I2C2_BASEADDR                  (APB1_BASEADDR + 0x5800UL)
#define I2C3_BASEADDR                  (APB1_BASEADDR + 0x5C00UL)
#define CAN1_BASEADDR                  (APB1_BASEADDR + 0x6400UL)
#define DAC_BASEADDR                   (APB1_BASEADDR + 0x7400UL)

/*******************************************************************************
 * APB2 peripheral base addresses
 ******************************************************************************/

#define TIM1_BASEADDR                  (APB2_BASEADDR + 0x0000UL)
#define USART1_BASEADDR                (APB2_BASEADDR + 0x1000UL)

#define ADC1_BASEADDR                  (APB2_BASEADDR + 0x2000UL)
#define ADC2_BASEADDR                  (APB2_BASEADDR + 0x2100UL)
#define ADC3_BASEADDR                  (APB2_BASEADDR + 0x2200UL)
#define ADC_COMMON_BASEADDR            (APB2_BASEADDR + 0x2300UL)

#define SPI1_BASEADDR                  (APB2_BASEADDR + 0x3000UL)
#define SYSCFG_BASEADDR                (APB2_BASEADDR + 0x3800UL)
#define EXTI_BASEADDR                  (APB2_BASEADDR + 0x3C00UL)


/*******************************************************************************
 * GPIO register definition
 ******************************************************************************/
typedef struct
{
	volatile uint32_t MODER; // GPIO mode register with offset  0x00
	volatile uint32_t OTYPER; //  output type register with offset 0x04
	volatile uint32_t OSPEEDR; // output speed register with offset 0x08
	volatile uint32_t PUPDR; // pull-up/pull-down register with offset 0x0C
	volatile uint32_t IDR; // input data register with offset 0x10
	volatile uint32_t ODR; //output data register with offset 0x14
	volatile uint32_t BSRR; //bit set/reset register with offset 0x18
	volatile uint32_t LCKR; //configuration lock register with offset 0x1C
	volatile uint32_t AFRL; //alternate function low register with offset 0x20
	volatile uint32_t AFRH; //alternate function High register with offset 0x24
} GPIO_RegDef_t;

/*******************************************************************************
 * GPIO peripheral definitions
 ******************************************************************************/
#define GPIOA                         ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB                         ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC                         ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD                         ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE                         ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF                         ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG                         ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH                         ((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI                         ((GPIO_RegDef_t *)GPIOI_BASEADDR)

/*******************************************************************************
 * EXTI register definition structure
 ******************************************************************************/

typedef struct
{
    volatile uint32_t IMR;      // Interrupt mask register with Offset 0x00
    volatile uint32_t EMR;      // Event mask register with Offset 0x04
    volatile uint32_t RTSR;     // Rising trigger selection register with Offset 0x08
    volatile uint32_t FTSR;     // Falling trigger selection register with Offset 0x0C
    volatile uint32_t SWIER;    // Software interrupt event register with Offset 0x10
    volatile uint32_t PR;       // Pending register with Offset 0x14

} EXTI_RegDef_t;

/*******************************************************************************
 * EXTI peripheral definition
 ******************************************************************************/

#define EXTI    ((EXTI_RegDef_t *)EXTI_BASEADDR)


/*******************************************************************************
 * SYSCFG register definition structure
 ******************************************************************************/

typedef struct
{
    volatile uint32_t MEMRMP;        // Memory remap register with Offset 0x00
    volatile uint32_t PMC;           // Peripheral mode configuration register with Offset 0x04
    volatile uint32_t EXTICR[4];     // External interrupt configuration registers with Offsets 0x08 - 0x14
    uint32_t RESERVED1[2];           // Reserved with Offsets 0x18 and 0x1C
    volatile uint32_t CMPCR;         // Compensation cell control register with Offset 0x20

} SYSCFG_RegDef_t;

/*******************************************************************************
 * SYSCFG peripheral definition
 ******************************************************************************/

#define SYSCFG                       ((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)

/*******************************************************************************
 * Returns port code for given GPIOx address
 ******************************************************************************/
#define GPIO_BASEADDR_TO_CODE(x)    (((x) == GPIOA) ? 0U : \
                                     ((x) == GPIOB) ? 1U : \
                                     ((x) == GPIOC) ? 2U : \
                                     ((x) == GPIOD) ? 3U : \
                                     ((x) == GPIOE) ? 4U : \
                                     ((x) == GPIOF) ? 5U : \
                                     ((x) == GPIOG) ? 6U : \
                                     ((x) == GPIOH) ? 7U : \
                                     ((x) == GPIOI) ? 8U : 0xFFU)

/*******************************************************************************
 * I2C register definition structure
 ******************************************************************************/

typedef struct
{
    volatile uint32_t CR1;       // Control register 1 with Offset 0x00
    volatile uint32_t CR2;       // Control register 2 with Offset 0x04
    volatile uint32_t OAR1;      // Own address register 1 with Offset 0x08
    volatile uint32_t OAR2;      // Own address register 2 with Offset 0x0C
    volatile uint32_t DR;        // Data register with Offset 0x10
    volatile uint32_t SR1;       // Status register 1 with Offset 0x14
    volatile uint32_t SR2;       // Status register 2 with Offset 0x18
    volatile uint32_t CCR;       // Clock control register with Offset 0x1C
    volatile uint32_t TRISE;     // TRISE register with Offset 0x20
    volatile uint32_t FLTR;      // Filter register with Offset 0x24

} I2C_RegDef_t;

/*******************************************************************************
 * I2C peripheral definitions
 ******************************************************************************/

#define I2C1    ((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2    ((I2C_RegDef_t *)I2C2_BASEADDR)
#define I2C3    ((I2C_RegDef_t *)I2C3_BASEADDR)

/*******************************************************************************
 * RCC register definition
 ******************************************************************************/

typedef struct
{
	volatile uint32_t CR; // clock control register with offset  0x00
	volatile uint32_t PLLCFGR; // configuration register with offset 0x04
	volatile uint32_t CFGR; // clock configuration register with offset 0x08
	volatile uint32_t CIR; // clock interrupt register register with offset 0x0C
	volatile uint32_t AHB1RSTR; // peripheral reset register for AHB1 with offset 0x10
	volatile uint32_t AHB2RSTR; //peripheral reset register for AHB2 with offset 0x14
	volatile uint32_t AHB3RSTR; //peripheral reset register for AHB3 with offset 0x18
	uint32_t RESERVED0; //Reserved with offset 0x1C
	volatile uint32_t APB1RSTR; //peripheral reset register for APB1 with offset 0x20
	volatile uint32_t APB2RSTR; //peripheral reset register for APB2 with offset 0x24
	uint32_t RESERVED1[2]; //Reserved with offset 0x28-0x2C
	volatile uint32_t AHB1ENR; //peripheral clock enable register for AHB1 with offset 0x30
	volatile uint32_t AHB2ENR; //peripheral clock enable register for AHB2 with offset 0x34
	volatile uint32_t AHB3ENR; //peripheral clock enable register for AHB3 with offset 0x38
	uint32_t RESERVED2; //Reserved with offset 0x3C
	volatile uint32_t APB1ENR; //peripheral clock enable register for APB1 with offset 0x40
	volatile uint32_t APB2ENR; //peripheral clock enable register for APB2 with offset 0x44
	uint32_t RESERVED3[2]; //Reserved with offset 0x48-0x4C
	volatile uint32_t AHB1LPENR; //peripheral clock enable in low power mode register for AHB1 with offset 0x50
	volatile uint32_t AHB2LPENR; //peripheral clock enable in low power mode register for AHB2 with offset 0x54
	volatile uint32_t AHB3LPENR; //peripheral clock enable in low power mode register for AHB3 with offset 0x58
	uint32_t RESERVED4; //Reserved with offset 0x5C
	volatile uint32_t APB1LPENR; //peripheral clock enable in low power mode register for APB1 with offset 0x60
	volatile uint32_t APB2LPENR; //peripheral clock enable in low power mode register for APB2 with offset 0x64
	uint32_t RESERVED5[2]; //Reserved with offset 0x68-0x6C
	volatile uint32_t BDCR; //Backup domain control register with offset 0x70
	volatile uint32_t CSR; //clock control & status register with offset 0x74
	uint32_t RESERVED6[2]; //Reserved with offset 0x78-0x7C
	volatile uint32_t SSCGR; //Spread spectrum clock generation register with offset 0x80
	volatile uint32_t PLLI2SCFGR; //PLLI2S configuration register with offset 0x84

} RCC_RegDef_t;

/*******************************************************************************
 * RCC peripheral definition
 ******************************************************************************/

#define RCC                           ((RCC_RegDef_t *)RCC_BASEADDR)

/*******************************************************************************
 * RCC AHB1 peripheral clock-enable bits
 ******************************************************************************/

#define RCC_AHB1ENR_GPIOAEN_Pos        0U
#define RCC_AHB1ENR_GPIOAEN_Msk        (1U << RCC_AHB1ENR_GPIOAEN_Pos)

#define RCC_AHB1ENR_GPIOBEN_Pos        1U
#define RCC_AHB1ENR_GPIOBEN_Msk        (1U << RCC_AHB1ENR_GPIOBEN_Pos)

#define RCC_AHB1ENR_GPIOCEN_Pos        2U
#define RCC_AHB1ENR_GPIOCEN_Msk        (1U << RCC_AHB1ENR_GPIOCEN_Pos)

#define RCC_AHB1ENR_GPIODEN_Pos        3U
#define RCC_AHB1ENR_GPIODEN_Msk        (1U << RCC_AHB1ENR_GPIODEN_Pos)

/*******************************************************************************
 * RCC AHB1 peripheral reset bits
 ******************************************************************************/

#define RCC_AHB1RSTR_GPIOARST_Pos        0U
#define RCC_AHB1RSTR_GPIOARST_Msk        (1U << RCC_AHB1RSTR_GPIOARST_Pos)

#define RCC_AHB1RSTR_GPIOBRST_Pos        1U
#define RCC_AHB1RSTR_GPIOBRST_Msk        (1U << RCC_AHB1RSTR_GPIOBRST_Pos)

#define RCC_AHB1RSTR_GPIOCRST_Pos        2U
#define RCC_AHB1RSTR_GPIOCRST_Msk        (1U << RCC_AHB1RSTR_GPIOCRST_Pos)

#define RCC_AHB1RSTR_GPIODRST_Pos        3U
#define RCC_AHB1RSTR_GPIODRST_Msk        (1U << RCC_AHB1RSTR_GPIODRST_Pos)

/*******************************************************************************
 * RCC APB1 peripheral clock-enable bits
 ******************************************************************************/

#define RCC_APB1ENR_USART2EN_Pos       17U
#define RCC_APB1ENR_USART2EN_Msk       (1U << RCC_APB1ENR_USART2EN_Pos)

#define RCC_APB1ENR_UART4EN_Pos        19U
#define RCC_APB1ENR_UART4EN_Msk        (1U << RCC_APB1ENR_UART4EN_Pos)

#define RCC_APB1ENR_I2C1EN_Pos         21U
#define RCC_APB1ENR_I2C1EN_Msk         (1U << RCC_APB1ENR_I2C1EN_Pos)

#define RCC_APB1ENR_I2C2EN_Pos       22U
#define RCC_APB1ENR_I2C2EN_Msk       (1U << RCC_APB1ENR_I2C2EN_Pos)

#define RCC_APB1ENR_I2C3EN_Pos       23U
#define RCC_APB1ENR_I2C3EN_Msk       (1U << RCC_APB1ENR_I2C3EN_Pos)


/*******************************************************************************
 * RCC APB1  peripheral reset bits
 ******************************************************************************/

#define RCC_APB1RSTR_I2C1RST_Pos     21U
#define RCC_APB1RSTR_I2C1RST_Msk     (1U << RCC_APB1RSTR_I2C1RST_Pos)

#define RCC_APB1RSTR_I2C2RST_Pos     22U
#define RCC_APB1RSTR_I2C2RST_Msk     (1U << RCC_APB1RSTR_I2C2RST_Pos)

#define RCC_APB1RSTR_I2C3RST_Pos     23U
#define RCC_APB1RSTR_I2C3RST_Msk     (1U << RCC_APB1RSTR_I2C3RST_Pos)


/*******************************************************************************
 * RCC APB2 peripheral clock-enable bits
 ******************************************************************************/

#define RCC_APB2ENR_USART1EN_Pos       4U
#define RCC_APB2ENR_USART1EN_Msk       (1U << RCC_APB2ENR_USART1EN_Pos)

#define RCC_APB2ENR_ADC1EN_Pos         8U
#define RCC_APB2ENR_ADC1EN_Msk         (1U << RCC_APB2ENR_ADC1EN_Pos)

#define RCC_APB2ENR_ADC2EN_Pos         9U
#define RCC_APB2ENR_ADC2EN_Msk         (1U << RCC_APB2ENR_ADC2EN_Pos)

#define RCC_APB2ENR_ADC3EN_Pos         10U
#define RCC_APB2ENR_ADC3EN_Msk         (1U << RCC_APB2ENR_ADC3EN_Pos)

#define RCC_APB2ENR_SYSCFGEN_Pos       14U
#define RCC_APB2ENR_SYSCFGEN_Msk       (1U << RCC_APB2ENR_SYSCFGEN_Pos)

/*******************************************************************************
 * I2C Control Register 1 (I2C_CR1) bit definitions
 ******************************************************************************/

#define I2C_CR1_PE_Pos                 0U
#define I2C_CR1_PE_Msk                 (1U << I2C_CR1_PE_Pos)

#define I2C_CR1_SMBUS_Pos              1U
#define I2C_CR1_SMBUS_Msk              (1U << I2C_CR1_SMBUS_Pos)

#define I2C_CR1_SMBTYPE_Pos            3U
#define I2C_CR1_SMBTYPE_Msk            (1U << I2C_CR1_SMBTYPE_Pos)

#define I2C_CR1_ENARP_Pos              4U
#define I2C_CR1_ENARP_Msk              (1U << I2C_CR1_ENARP_Pos)

#define I2C_CR1_ENPEC_Pos              5U
#define I2C_CR1_ENPEC_Msk              (1U << I2C_CR1_ENPEC_Pos)

#define I2C_CR1_ENGC_Pos               6U
#define I2C_CR1_ENGC_Msk               (1U << I2C_CR1_ENGC_Pos)

#define I2C_CR1_NOSTRETCH_Pos          7U
#define I2C_CR1_NOSTRETCH_Msk          (1U << I2C_CR1_NOSTRETCH_Pos)

#define I2C_CR1_START_Pos              8U
#define I2C_CR1_START_Msk              (1U << I2C_CR1_START_Pos)

#define I2C_CR1_STOP_Pos               9U
#define I2C_CR1_STOP_Msk               (1U << I2C_CR1_STOP_Pos)

#define I2C_CR1_ACK_Pos               10U
#define I2C_CR1_ACK_Msk               (1U << I2C_CR1_ACK_Pos)

#define I2C_CR1_POS_Pos               11U
#define I2C_CR1_POS_Msk               (1U << I2C_CR1_POS_Pos)

#define I2C_CR1_PEC_Pos               12U
#define I2C_CR1_PEC_Msk               (1U << I2C_CR1_PEC_Pos)

#define I2C_CR1_ALERT_Pos             13U
#define I2C_CR1_ALERT_Msk             (1U << I2C_CR1_ALERT_Pos)

#define I2C_CR1_SWRST_Pos             15U
#define I2C_CR1_SWRST_Msk             (1U << I2C_CR1_SWRST_Pos)


/*******************************************************************************
 * I2C Control Register 2 (I2C_CR2) bit definitions
 ******************************************************************************/

#define I2C_CR2_FREQ_Pos               0U
#define I2C_CR2_FREQ_Msk               (0x3FU << I2C_CR2_FREQ_Pos)

#define I2C_CR2_ITERREN_Pos            8U
#define I2C_CR2_ITERREN_Msk            (1U << I2C_CR2_ITERREN_Pos)

#define I2C_CR2_ITEVTEN_Pos            9U
#define I2C_CR2_ITEVTEN_Msk            (1U << I2C_CR2_ITEVTEN_Pos)

#define I2C_CR2_ITBUFEN_Pos           10U
#define I2C_CR2_ITBUFEN_Msk           (1U << I2C_CR2_ITBUFEN_Pos)

#define I2C_CR2_DMAEN_Pos             11U
#define I2C_CR2_DMAEN_Msk             (1U << I2C_CR2_DMAEN_Pos)

#define I2C_CR2_LAST_Pos              12U
#define I2C_CR2_LAST_Msk              (1U << I2C_CR2_LAST_Pos)

/*******************************************************************************
 * I2C Own Address Register 1 (I2C_OAR1) bit definitions
 ******************************************************************************/

#define I2C_OAR1_ADD0_Pos              0U
#define I2C_OAR1_ADD0_Msk              (1U << I2C_OAR1_ADD0_Pos)

#define I2C_OAR1_ADD7_1_Pos            1U
#define I2C_OAR1_ADD7_1_Msk            (0x7FU << I2C_OAR1_ADD7_1_Pos)

#define I2C_OAR1_ADD9_8_Pos            8U
#define I2C_OAR1_ADD9_8_Msk            (0x3U << I2C_OAR1_ADD9_8_Pos)

/*
 * RM0090 requires bit 14 of I2C_OAR1 to always be kept at 1 by software.
 */
#define I2C_OAR1_BIT14_Pos            14U
#define I2C_OAR1_BIT14_Msk            (1U << I2C_OAR1_BIT14_Pos)

#define I2C_OAR1_ADDMODE_Pos          15U
#define I2C_OAR1_ADDMODE_Msk          (1U << I2C_OAR1_ADDMODE_Pos)

/*******************************************************************************
 * I2C Own Address Register 2 (I2C_OAR2) bit definitions
 ******************************************************************************/

#define I2C_OAR2_ENDUAL_Pos            0U
#define I2C_OAR2_ENDUAL_Msk            (1U << I2C_OAR2_ENDUAL_Pos)

#define I2C_OAR2_ADD2_Pos              1U
#define I2C_OAR2_ADD2_Msk              (0x7FU << I2C_OAR2_ADD2_Pos)

/*******************************************************************************
 * I2C Data Register (I2C_DR) bit definitions
 ******************************************************************************/

#define I2C_DR_DR_Pos                  0U
#define I2C_DR_DR_Msk                  (0xFFU << I2C_DR_DR_Pos)

/*******************************************************************************
 * I2C Status Register 1 (I2C_SR1) bit definitions
 ******************************************************************************/

#define I2C_SR1_SB_Pos                 0U
#define I2C_SR1_SB_Msk                 (1U << I2C_SR1_SB_Pos)

#define I2C_SR1_ADDR_Pos               1U
#define I2C_SR1_ADDR_Msk               (1U << I2C_SR1_ADDR_Pos)

#define I2C_SR1_BTF_Pos                2U
#define I2C_SR1_BTF_Msk                (1U << I2C_SR1_BTF_Pos)

#define I2C_SR1_ADD10_Pos              3U
#define I2C_SR1_ADD10_Msk              (1U << I2C_SR1_ADD10_Pos)

#define I2C_SR1_STOPF_Pos              4U
#define I2C_SR1_STOPF_Msk              (1U << I2C_SR1_STOPF_Pos)

#define I2C_SR1_RXNE_Pos               6U
#define I2C_SR1_RXNE_Msk               (1U << I2C_SR1_RXNE_Pos)

#define I2C_SR1_TXE_Pos                7U
#define I2C_SR1_TXE_Msk                (1U << I2C_SR1_TXE_Pos)

#define I2C_SR1_BERR_Pos               8U
#define I2C_SR1_BERR_Msk               (1U << I2C_SR1_BERR_Pos)

#define I2C_SR1_ARLO_Pos               9U
#define I2C_SR1_ARLO_Msk               (1U << I2C_SR1_ARLO_Pos)

#define I2C_SR1_AF_Pos                10U
#define I2C_SR1_AF_Msk                (1U << I2C_SR1_AF_Pos)

#define I2C_SR1_OVR_Pos               11U
#define I2C_SR1_OVR_Msk               (1U << I2C_SR1_OVR_Pos)

#define I2C_SR1_PECERR_Pos            12U
#define I2C_SR1_PECERR_Msk            (1U << I2C_SR1_PECERR_Pos)

#define I2C_SR1_TIMEOUT_Pos           14U
#define I2C_SR1_TIMEOUT_Msk           (1U << I2C_SR1_TIMEOUT_Pos)

#define I2C_SR1_SMBALERT_Pos          15U
#define I2C_SR1_SMBALERT_Msk          (1U << I2C_SR1_SMBALERT_Pos)

/*******************************************************************************
 * I2C Status Register 2 (I2C_SR2) bit definitions
 ******************************************************************************/

#define I2C_SR2_MSL_Pos                0U
#define I2C_SR2_MSL_Msk                (1U << I2C_SR2_MSL_Pos)

#define I2C_SR2_BUSY_Pos               1U
#define I2C_SR2_BUSY_Msk               (1U << I2C_SR2_BUSY_Pos)

#define I2C_SR2_TRA_Pos                2U
#define I2C_SR2_TRA_Msk                (1U << I2C_SR2_TRA_Pos)

#define I2C_SR2_GENCALL_Pos            4U
#define I2C_SR2_GENCALL_Msk            (1U << I2C_SR2_GENCALL_Pos)

#define I2C_SR2_SMBDEFAULT_Pos         5U
#define I2C_SR2_SMBDEFAULT_Msk         (1U << I2C_SR2_SMBDEFAULT_Pos)

#define I2C_SR2_SMBHOST_Pos            6U
#define I2C_SR2_SMBHOST_Msk            (1U << I2C_SR2_SMBHOST_Pos)

#define I2C_SR2_DUALF_Pos              7U
#define I2C_SR2_DUALF_Msk              (1U << I2C_SR2_DUALF_Pos)

#define I2C_SR2_PEC_Pos                8U
#define I2C_SR2_PEC_Msk                (0xFFU << I2C_SR2_PEC_Pos)

/*******************************************************************************
 * I2C Clock Control Register (I2C_CCR) bit definitions
 ******************************************************************************/

#define I2C_CCR_CCR_Pos                0U
#define I2C_CCR_CCR_Msk                (0xFFFU << I2C_CCR_CCR_Pos)

#define I2C_CCR_DUTY_Pos              14U
#define I2C_CCR_DUTY_Msk              (1U << I2C_CCR_DUTY_Pos)

#define I2C_CCR_FS_Pos                15U
#define I2C_CCR_FS_Msk                (1U << I2C_CCR_FS_Pos)

/*******************************************************************************
 * I2C TRISE Register (I2C_TRISE) bit definitions
 ******************************************************************************/

#define I2C_TRISE_TRISE_Pos            0U
#define I2C_TRISE_TRISE_Msk            (0x3FU << I2C_TRISE_TRISE_Pos)

/*******************************************************************************
 * I2C Filter Register (I2C_FLTR) bit definitions
 ******************************************************************************/

#define I2C_FLTR_DNF_Pos               0U
#define I2C_FLTR_DNF_Msk               (0xFU << I2C_FLTR_DNF_Pos)

#define I2C_FLTR_ANOFF_Pos             4U
#define I2C_FLTR_ANOFF_Msk             (1U << I2C_FLTR_ANOFF_Pos)



/*******************************************************************************
 * IRQ numbers for EXTI interrupt lines
 *
 * These values correspond to the NVIC interrupt request numbers used to
 * enable, disable, and prioritize EXTI interrupts.
 *
 * EXTI lines 0 to 4 have individual IRQ numbers.
 * EXTI lines 5 to 9 share one IRQ number.
 * EXTI lines 10 to 15 share one IRQ number.
 ******************************************************************************/

#define IRQ_NO_EXTI0          6U
#define IRQ_NO_EXTI1          7U
#define IRQ_NO_EXTI2          8U
#define IRQ_NO_EXTI3          9U
#define IRQ_NO_EXTI4         10U
#define IRQ_NO_EXTI9_5       23U
#define IRQ_NO_EXTI15_10     40U


/*******************************************************************************
 * IRQ numbers for I2C peripherals
 ******************************************************************************/

#define IRQ_NO_I2C1_EV               31U
#define IRQ_NO_I2C1_ER               32U

#define IRQ_NO_I2C2_EV               33U
#define IRQ_NO_I2C2_ER               34U

#define IRQ_NO_I2C3_EV               72U
#define IRQ_NO_I2C3_ER               73U


/*******************************************************************************
 * NVIC Interrupt Priority Levels
 *
 * The STM32F4 family implements 4 bits for interrupt priority, resulting in
 * 16 programmable priority levels.
 *
 * Note: A lower numerical value corresponds to a higher logical priority.
 *       Level 0 is the highest priority, and Level 15 is the lowest.
 ******************************************************************************/

#define NVIC_IRQ_PRIO_0       0U  /* Highest priority */
#define NVIC_IRQ_PRIO_1       1U
#define NVIC_IRQ_PRIO_2       2U
#define NVIC_IRQ_PRIO_3       3U
#define NVIC_IRQ_PRIO_4       4U
#define NVIC_IRQ_PRIO_5       5U
#define NVIC_IRQ_PRIO_6       6U
#define NVIC_IRQ_PRIO_7       7U
#define NVIC_IRQ_PRIO_8       8U
#define NVIC_IRQ_PRIO_9       9U
#define NVIC_IRQ_PRIO_10     10U
#define NVIC_IRQ_PRIO_11     11U
#define NVIC_IRQ_PRIO_12     12U
#define NVIC_IRQ_PRIO_13     13U
#define NVIC_IRQ_PRIO_14     14U
#define NVIC_IRQ_PRIO_15     15U  /* Lowest priority */


/*******************************************************************************
 * Generic macros
 ******************************************************************************/
#define ENABLE               1U
#define DISABLE              0U
#define RESET                DISABLE
#define SET                  ENABLE
#define GPIO_PIN_SET         SET
#define GPIO_PIN_RESET       RESET

#endif /* INC_STM32F407XX_H_ */

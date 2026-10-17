\# STM32F407 Bare-Metal Driver Library



Bare-metal peripheral drivers written in C for the STM32F407VGT6

microcontroller using register-level programming without STM32 HAL.



\## Hardware

\- Board: STM32F407G-DISC1

\- MCU: STM32F407VGT6

\- Core: ARM Cortex-M4



\## Driver Status

\- GPIO: Implemented

\- I2C: In development

\- SPI: Planned

\- USART: Planned



\## Project Structure

\- Drivers/Inc: Device definitions and driver interfaces

\- Drivers/Src: Peripheral driver implementations

\- Src: Small hardware validation applications

\- Startup: Startup assembly code



\## Development Approach

Drivers are implemented from the STM32 reference manual.

Each driver is reviewed and tested independently before

larger embedded applications are developed.


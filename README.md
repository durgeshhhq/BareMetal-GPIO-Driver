# BareMetal-GPIO-Driver
Register-level GPIO driver for STM32F446RE ARM Cortex-M4, developed in Embedded C with GPIO configuration, digital I/O, alternate functions, EXTI interrupts, and NVIC support.
# STM32F407 Register-Level GPIO Driver

A reusable **bare-metal GPIO device driver** developed for the **STM32F446RE ARM Cortex-M4** microcontroller using **Embedded C**.

The driver is implemented using direct memory-mapped register access without depending on the STM32 HAL GPIO APIs. It provides configurable GPIO initialization, digital I/O operations, alternate-function configuration, peripheral clock control, and EXTI/NVIC-based interrupt handling.

## Features

* Register-level GPIO programming
* GPIO input configuration
* GPIO output configuration
* Alternate-function configuration
* Analog mode configuration
* Push-pull and open-drain output modes
* GPIO speed configuration
* Pull-up / pull-down configuration
* GPIO pin read
* GPIO port read
* GPIO pin write
* GPIO port write
* GPIO pin toggle
* GPIO peripheral clock control
* GPIO peripheral reset
* EXTI interrupt configuration

  * Rising edge
  * Falling edge
  * Rising + falling edge
* NVIC interrupt enable/disable
* NVIC interrupt priority configuration
* EXTI interrupt handling

## Target Platform

| Parameter            | Description                 |
| -------------------- | --------------------------- |
| MCU                  | STM32F446RE                   |
| CPU                  | ARM Cortex-M4               |
| Language             | Embedded C                  |
| Driver Type          | Bare-Metal / Register-Level |
| GPIO Ports           | GPIOA – GPIOI               |
| Interrupt Controller | ARM Cortex-M NVIC           |
| External Interrupt   | STM32 EXTI                  |

## Driver Architecture

```text
+-----------------------------+
|        Application          |
+-----------------------------+
              |
              v
+-----------------------------+
|        GPIO Driver API      |
|                             |
| GPIO_Init()                 |
| GPIO_ReadFromInputPin()     |
| GPIO_WriteToOutputPin()     |
| GPIO_ToggleOutputPin()      |
| GPIO_DeInit()               |
+-----------------------------+
              |
              v
+-----------------------------+
|   Register-Level Access     |
|                             |
| MODER                       |
| OTYPER                      |
| OSPEEDR                     |
| PUPDR                       |
| IDR / ODR                   |
| AFR                         |
+-----------------------------+
              |
              v
+-----------------------------+
|        STM32F446 MCU        |
+-----------------------------+
```

## GPIO Configuration

The driver uses a configuration structure to describe the desired GPIO settings:

```c
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_t;
```

A handle structure associates the configuration with a GPIO peripheral:

```c
typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;

} GPIO_Handle_t;
```

This separates **GPIO configuration data** from the driver implementation and allows the same driver APIs to be reused for different GPIO ports and pins.

## Example

```c
GPIO_Handle_t GPIO_LED;

GPIO_LED.pGPIOx = GPIOD;

GPIO_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
GPIO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
GPIO_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

GPIO_Init(&GPIO_LED);

GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_SET);
```

## EXTI Interrupt Support

The driver supports GPIO external interrupts through the STM32F446 EXTI controller.

```text
GPIO Pin
   |
   v
 SYSCFG
   |
   v
 EXTI
   |
   v
 NVIC
   |
   v
 Interrupt Service Routine
   |
   v
GPIO_IRQHandling()
```

Supported trigger configurations:

* Falling edge
* Rising edge
* Rising and falling edge

The driver also provides NVIC interrupt enable/disable and priority configuration APIs.

## Register-Level Implementation

The project defines peripheral register structures and maps them to the STM32F446 peripheral base addresses.

For example:

```c
typedef struct
{
    __vo uint32_t MODER;
    __vo uint32_t OTYPER;
    __vo uint32_t OSPEEDR;
    __vo uint32_t PUPDR;
    __vo uint32_t IDR;
    __vo uint32_t ODR;
    __vo uint32_t BSRR;
    __vo uint32_t LCKR;
    __vo uint32_t AFR[2];

} GPIO_RegDef_t;
```

The GPIO peripheral is then accessed through its memory-mapped address:

```c
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
```

This provides direct access to the STM32F446RE GPIO hardware registers.

## Project Objectives

1. Understand the STM32F446RE GPIO peripheral at the register level.
2. Develop a reusable GPIO driver without relying on vendor GPIO HAL APIs.
3. Implement configurable GPIO initialization.
4. Implement GPIO digital I/O APIs.
5. Integrate GPIO with the EXTI and NVIC interrupt mechanisms.
6. Validate the driver on STM32F446 hardware.

## Testing

The driver should be validated using the following test cases:

| Test               | Description                  | Expected Result               |
| ------------------ | ---------------------------- | ----------------------------- |
| GPIO Output        | Configure pin as output      | Pin changes state correctly   |
| GPIO Input         | Configure pin as input       | Input state is read correctly |
| Toggle             | Toggle GPIO output           | Output changes state          |
| Pull-up            | Enable internal pull-up      | Input defaults HIGH           |
| Pull-down          | Enable internal pull-down    | Input defaults LOW            |
| Alternate Function | Configure alternate function | Correct AF selected           |
| EXTI Rising        | Rising-edge interrupt        | ISR triggered                 |
| EXTI Falling       | Falling-edge interrupt       | ISR triggered                 |
| EXTI Both          | Both-edge interrupt          | ISR triggered on both edges   |

## Future Improvements

* Add BSRR-based atomic GPIO output operations
* Complete GPIO clock-disable APIs
* Add automated unit testing for driver logic
* Measure GPIO API execution time using DWT cycle counter
* Measure interrupt latency
* Compare register-level driver performance with STM32 HAL
* Analyze Flash and RAM footprint
* Add logic-analyzer/oscilloscope validation results

## Skills Demonstrated

**Embedded C • ARM Cortex-M4 • STM32F446RE • Bare-Metal Programming • Device Drivers • Memory-Mapped I/O • GPIO • EXTI • NVIC • Interrupt Handling • Peripheral Registers**

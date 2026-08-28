/*
 * stm32f446xx_gpio_driver.h
 *
 * Register-level GPIO driver for STM32F446RE
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"


/***************************************************************
 * GPIO pin configuration structure
 ***************************************************************/

typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFunMode;

} GPIO_PinConfig_t;


/***************************************************************
 * GPIO handle structure
 ***************************************************************/

typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;

} GPIO_Handle_t;


/***************************************************************
 * Generic macros
 ***************************************************************/

#define ENABLE              1
#define DISABLE             0

#define SET                 ENABLE
#define RESET               DISABLE

#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET


/***************************************************************
 * GPIO pin numbers
 ***************************************************************/

#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15


/***************************************************************
 * GPIO pin modes
 *
 * MODER:
 *
 * 00 = Input
 * 01 = General purpose output
 * 10 = Alternate function
 * 11 = Analog
 ***************************************************************/

#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3

/*
 * Interrupt modes
 */
#define GPIO_MODE_IT_FT     4
#define GPIO_MODE_IT_RT     5
#define GPIO_MODE_IT_RFT    6


/***************************************************************
 * GPIO output types
 ***************************************************************/

#define GPIO_OP_TYPE_PP     0
#define GPIO_OP_TYPE_OD     1


/***************************************************************
 * GPIO output speed
 ***************************************************************/

#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3


/***************************************************************
 * GPIO pull-up / pull-down
 *
 * 00 = No pull
 * 01 = Pull-up
 * 10 = Pull-down
 ***************************************************************/

#define GPIO_NO_PUPD        0
#define GPIO_PIN_PU         1
#define GPIO_PIN_PD         2


/***************************************************************
 * EXTI IRQ numbers for STM32F446
 ***************************************************************/

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10

#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40


/***************************************************************
 * GPIO port to EXTI mapping
 *
 * Port code:
 *
 * GPIOA = 0000
 * GPIOB = 0001
 * GPIOC = 0010
 * GPIOD = 0011
 * GPIOE = 0100
 * GPIOF = 0101
 * GPIOG = 0110
 * GPIOH = 0111
 ***************************************************************/

#define GPIO_BASEADDR_TO_CODE(x)     \
    ((x == GPIOA) ? 0U :             \
     (x == GPIOB) ? 1U :             \
     (x == GPIOC) ? 2U :             \
     (x == GPIOD) ? 3U :             \
     (x == GPIOE) ? 4U :             \
     (x == GPIOF) ? 5U :             \
     (x == GPIOG) ? 6U :             \
     (x == GPIOH) ? 7U : 0U)


/***************************************************************
 * GPIO APIs
 ***************************************************************/

/*
 * Peripheral clock control
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/*
 * GPIO initialization / deinitialization
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * GPIO input APIs
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,
                              uint8_t PinNumber);

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);


/*
 * GPIO output APIs
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t Value);

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t Value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber);


/*
 * GPIO interrupt APIs
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,
                             uint8_t EnorDi);

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,
                            uint32_t IRQPriority);

void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */

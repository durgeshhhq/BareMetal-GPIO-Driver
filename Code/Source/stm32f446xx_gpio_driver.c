/*
 * stm32f446xx_gpio_driver.c
 *
 * Register-level GPIO driver implementation
 * Target: STM32F446RE
 */

#include "stm32f446xx_gpio_driver.h"


/***************************************************************
 * Private helper functions
 ***************************************************************/

static uint8_t GPIO_IsValidPinNumber(uint8_t PinNumber)
{
    return (PinNumber <= 15U);
}


static uint8_t GPIO_IsValidPort(GPIO_RegDef_t *pGPIOx)
{
    if((pGPIOx == GPIOA) ||
       (pGPIOx == GPIOB) ||
       (pGPIOx == GPIOC) ||
       (pGPIOx == GPIOD) ||
       (pGPIOx == GPIOE) ||
       (pGPIOx == GPIOF) ||
       (pGPIOx == GPIOG) ||
       (pGPIOx == GPIOH))
    {
        return 1U;
    }

    return 0U;
}


/***************************************************************
 * GPIO Peripheral Clock Control
 ***************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,
                           uint8_t EnorDi)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
    }
}


/***************************************************************
 * GPIO Initialization
 ***************************************************************/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0U;

    GPIO_RegDef_t *pGPIOx;
    uint8_t pinNumber;

    if(pGPIOHandle == 0)
    {
        return;
    }

    pGPIOx = pGPIOHandle->pGPIOx;
    pinNumber = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    if(!GPIO_IsValidPinNumber(pinNumber))
    {
        return;
    }


    /*
     * Enable GPIO peripheral clock
     */
    GPIO_PeriClockControl(pGPIOx, ENABLE);


    /***********************************************************
     * 1. Configure GPIO mode
     ***********************************************************/

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        /*
         * Clear the existing MODER bits
         */
        pGPIOx->MODER &= ~(0x3U << (2U * pinNumber));

        /*
         * Set new mode
         */
        temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
                << (2U * pinNumber));

        pGPIOx->MODER |= temp;
    }
    else
    {
        /*
         * Interrupt mode:
         *
         * GPIO must operate as input.
         */
        pGPIOx->MODER &= ~(0x3U << (2U * pinNumber));


        /*******************************************************
         * Configure trigger edge
         *******************************************************/

        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            /*
             * Falling edge
             */
            EXTI->FTSR |= (1U << pinNumber);

            /*
             * Disable rising edge
             */
            EXTI->RTSR &= ~(1U << pinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            /*
             * Rising edge
             */
            EXTI->RTSR |= (1U << pinNumber);

            /*
             * Disable falling edge
             */
            EXTI->FTSR &= ~(1U << pinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            /*
             * Both rising and falling edges
             */
            EXTI->RTSR |= (1U << pinNumber);
            EXTI->FTSR |= (1U << pinNumber);
        }
        else
        {
            return;
        }


        /*******************************************************
         * Configure GPIO port selection in SYSCFG_EXTICR
         *******************************************************/

        uint8_t temp1;
        uint8_t temp2;
        uint8_t portcode;

        temp1 = pinNumber / 4U;
        temp2 = pinNumber % 4U;

        portcode = GPIO_BASEADDR_TO_CODE(pGPIOx);

        /*
         * Enable SYSCFG clock
         */
        SYSCFG_PCLK_EN();

        /*
         * Clear the 4-bit field corresponding to this EXTI line.
         *
         * IMPORTANT:
         * Do not overwrite other EXTI configuration fields.
         */
        SYSCFG->EXTICR[temp1] &=
            ~(0xFU << (4U * temp2));

        SYSCFG->EXTICR[temp1] |=
            ((uint32_t)portcode << (4U * temp2));


        /*******************************************************
         * Enable interrupt delivery through EXTI IMR
         *******************************************************/

        EXTI->IMR |= (1U << pinNumber);
    }


    /***********************************************************
     * 2. Configure GPIO speed
     ***********************************************************/

    temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
            << (2U * pinNumber));

    pGPIOx->OSPEEDR &= ~(0x3U << (2U * pinNumber));

    pGPIOx->OSPEEDR |= temp;


    /***********************************************************
     * 3. Configure pull-up / pull-down
     ***********************************************************/

    temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
            << (2U * pinNumber));

    pGPIOx->PUPDR &= ~(0x3U << (2U * pinNumber));

    pGPIOx->PUPDR |= temp;


    /***********************************************************
     * 4. Configure output type
     ***********************************************************/

    temp = ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
            << pinNumber);

    pGPIOx->OTYPER &= ~(1U << pinNumber);

    pGPIOx->OTYPER |= temp;


    /***********************************************************
     * 5. Configure alternate function
     ***********************************************************/

    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1;
        uint8_t temp2;

        /*
         * Pins 0-7  -> AFR[0]
         * Pins 8-15 -> AFR[1]
         */
        temp1 = pinNumber / 8U;

        /*
         * Position of pin inside AFR register
         */
        temp2 = pinNumber % 8U;

        /*
         * Clear existing AF selection
         */
        pGPIOx->AFR[temp1] &=
            ~(0xFU << (4U * temp2));

        /*
         * Set requested AF
         */
        pGPIOx->AFR[temp1] |=
            ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode
             << (4U * temp2));
    }
}


/***************************************************************
 * GPIO DeInitialization
 ***************************************************************/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}


/***************************************************************
 * GPIO Read From Input Pin
 ***************************************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,
                              uint8_t PinNumber)
{
    uint8_t value;

    if(!GPIO_IsValidPort(pGPIOx))
    {
        return GPIO_PIN_RESET;
    }

    if(!GPIO_IsValidPinNumber(PinNumber))
    {
        return GPIO_PIN_RESET;
    }

    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1U);

    return value;
}


/***************************************************************
 * GPIO Read From Input Port
 ***************************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return 0U;
    }

    return (uint16_t)(pGPIOx->IDR & 0xFFFFU);
}


/***************************************************************
 * GPIO Write To Output Pin
 ***************************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t Value)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    if(!GPIO_IsValidPinNumber(PinNumber))
    {
        return;
    }

    /*
     * BSRR provides atomic set/reset operation.
     *
     * BSRR bits 0-15  -> set corresponding GPIO pin
     * BSRR bits 16-31 -> reset corresponding GPIO pin
     */

    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR = (1U << PinNumber);
    }
    else
    {
        pGPIOx->BSRR = (1U << (PinNumber + 16U));
    }
}


/***************************************************************
 * GPIO Write To Output Port
 ***************************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t Value)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    pGPIOx->ODR = (uint32_t)Value;
}


/***************************************************************
 * GPIO Toggle Output Pin
 ***************************************************************/

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber)
{
    if(!GPIO_IsValidPort(pGPIOx))
    {
        return;
    }

    if(!GPIO_IsValidPinNumber(PinNumber))
    {
        return;
    }

    pGPIOx->ODR ^= (1U << PinNumber);
}


/***************************************************************
 * NVIC IRQ Interrupt Configuration
 ***************************************************************/

void GPIO_IRQInterruptConfig(uint8_t IRQNumber,
                             uint8_t EnorDi)
{
    uint32_t bitNumber;

    /*
     * STM32F446 has 96 possible external IRQ positions
     * represented through ISER0-2.
     */
    if(IRQNumber >= 96U)
    {
        return;
    }

    bitNumber = IRQNumber % 32U;

    if(EnorDi == ENABLE)
    {
        if(IRQNumber < 32U)
        {
            *NVIC_ISER0 = (1U << bitNumber);
        }
        else if(IRQNumber < 64U)
        {
            *NVIC_ISER1 = (1U << bitNumber);
        }
        else
        {
            *NVIC_ISER2 = (1U << bitNumber);
        }
    }
    else
    {
        if(IRQNumber < 32U)
        {
            *NVIC_ICER0 = (1U << bitNumber);
        }
        else if(IRQNumber < 64U)
        {
            *NVIC_ICER1 = (1U << bitNumber);
        }
        else
        {
            *NVIC_ICER2 = (1U << bitNumber);
        }
    }
}


/***************************************************************
 * NVIC IRQ Priority Configuration
 ***************************************************************/

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,
                            uint32_t IRQPriority)
{
    uint8_t iprx;
    uint8_t iprx_section;
    uint8_t shift_amount;

    /*
     * Only external interrupt numbers are handled here.
     */
    if(IRQNumber >= 96U)
    {
        return;
    }

    /*
     * STM32F446 implements 4 priority bits.
     *
     * Therefore valid priority:
     *
     * 0 -> highest
     * 15 -> lowest
     */
    IRQPriority &= 0x0FU;


    /*
     * Find IPR register.
     *
     * Four IRQ priorities are stored in one 32-bit register.
     */
    iprx = IRQNumber / 4U;

    /*
     * Find the 8-bit field inside IPR.
     */
    iprx_section = IRQNumber % 4U;


    /*
     * Priority bits occupy the upper 4 bits
     * of each 8-bit priority field.
     *
     * 8 - 4 = 4
     */
    shift_amount =
        (8U * iprx_section) +
        (8U - NO_PR_BITS_IMPLEMENTED);


    /*
     * Clear existing priority field
     */
    NVIC_PR_BASE_ADDR[iprx] &=
        ~(0xFFU << shift_amount);


    /*
     * Set new priority
     */
    NVIC_PR_BASE_ADDR[iprx] |=
        (IRQPriority << shift_amount);
}


/***************************************************************
 * GPIO IRQ Handling
 ***************************************************************/

void GPIO_IRQHandling(uint8_t PinNumber)
{
    if(!GPIO_IsValidPinNumber(PinNumber))
    {
        return;
    }

    /*
     * Check whether the EXTI pending bit is set.
     */
    if(EXTI->PR & (1U << PinNumber))
    {
        /*
         * Clear pending bit.
         *
         * EXTI pending bits are cleared by writing 1.
         */
        EXTI->PR = (1U << PinNumber);
    }
}

//For a simple GPIO output test, suppose you connect an LED to PA5 with an appropriate resistor.
#include "stm32f446xx_gpio_driver.h"

static void delay(void)
{
    for(volatile uint32_t i = 0; i < 500000U; i++)
    {
        __asm volatile ("nop");
    }
}


int main(void)
{
    GPIO_Handle_t GPIO_LED;

    /*
     * Configure PA5 as GPIO output
     */
    GPIO_LED.pGPIOx = GPIOA;

    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber =
        GPIO_PIN_NO_5;

    GPIO_LED.GPIO_PinConfig.GPIO_PinMode =
        GPIO_MODE_OUT;

    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed =
        GPIO_SPEED_FAST;

    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl =
        GPIO_NO_PUPD;

    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType =
        GPIO_OP_TYPE_PP;

    GPIO_LED.GPIO_PinConfig.GPIO_PinAltFunMode =
        0;


    /*
     * Initialize GPIO
     */
    GPIO_Init(&GPIO_LED);


    while(1)
    {
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);

        delay();
    }
}

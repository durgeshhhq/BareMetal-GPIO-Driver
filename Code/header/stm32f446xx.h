/*
 * stm32f446xx.h
 *
 * STM32F446xx register definitions
 * Target: STM32F446RE
 *
 * Bare-metal register-level programming
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>

/*
 * Volatile qualifier
 *
 * Peripheral registers can change asynchronously with respect
 * to the CPU. Therefore they must be accessed through volatile.
 */
#define __vo volatile


/***************************************************************
 * Processor NVIC register addresses
 ***************************************************************/

#define NVIC_ISER0       ((volatile uint32_t *)0xE000E100UL)
#define NVIC_ISER1       ((volatile uint32_t *)0xE000E104UL)
#define NVIC_ISER2       ((volatile uint32_t *)0xE000E108UL)

#define NVIC_ICER0       ((volatile uint32_t *)0xE000E180UL)
#define NVIC_ICER1       ((volatile uint32_t *)0xE000E184UL)
#define NVIC_ICER2       ((volatile uint32_t *)0xE000E188UL)

#define NVIC_PR_BASE_ADDR ((volatile uint32_t *)0xE000E400UL)

/*
 * STM32F446 implements 4 priority bits.
 */
#define NO_PR_BITS_IMPLEMENTED       4U


/***************************************************************
 * Peripheral base addresses
 ***************************************************************/

/*
 * AHB1 peripheral base address
 */
#define AHB1PERIPH_BASEADDR          0x40020000UL

/*
 * APB2 peripheral base address
 */
#define APB2PERIPH_BASEADDR          0x40010000UL


/*
 * GPIO peripheral base addresses
 *
 * STM32F446RE:
 * GPIOA = 0x40020000
 * GPIOB = 0x40020400
 * GPIOC = 0x40020800
 * GPIOD = 0x40020C00
 * GPIOE = 0x40021000
 * GPIOF = 0x40021400
 * GPIOG = 0x40021800
 * GPIOH = 0x40021C00
 */
#define GPIOA_BASEADDR               (AHB1PERIPH_BASEADDR + 0x0000UL)
#define GPIOB_BASEADDR               (AHB1PERIPH_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR               (AHB1PERIPH_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR               (AHB1PERIPH_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR               (AHB1PERIPH_BASEADDR + 0x1000UL)
#define GPIOF_BASEADDR               (AHB1PERIPH_BASEADDR + 0x1400UL)
#define GPIOG_BASEADDR               (AHB1PERIPH_BASEADDR + 0x1800UL)
#define GPIOH_BASEADDR               (AHB1PERIPH_BASEADDR + 0x1C00UL)


/*
 * RCC base address
 */
#define RCC_BASEADDR                 (AHB1PERIPH_BASEADDR + 0x3800UL)


/*
 * APB2 peripherals
 *
 * EXTI   = 0x40013C00
 * SYSCFG = 0x40013800
 */
#define EXTI_BASEADDR                (APB2PERIPH_BASEADDR + 0x3C00UL)
#define SYSCFG_BASEADDR              (APB2PERIPH_BASEADDR + 0x3800UL)


/***************************************************************
 * Peripheral register definition structures
 ***************************************************************/


/*
 * GPIO register definition
 *
 * Offset:
 * MODER   0x00
 * OTYPER  0x04
 * OSPEEDR 0x08
 * PUPDR   0x0C
 * IDR     0x10
 * ODR     0x14
 * BSRR    0x18
 * LCKR    0x1C
 * AFRL    0x20
 * AFRH    0x24
 */
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


/*
 * RCC register definition
 */
typedef struct
{
    __vo uint32_t CR;             /* 0x00 */
    __vo uint32_t PLLCFGR;        /* 0x04 */
    __vo uint32_t CFGR;           /* 0x08 */
    __vo uint32_t CIR;            /* 0x0C */

    __vo uint32_t AHB1RSTR;       /* 0x10 */
    __vo uint32_t AHB2RSTR;       /* 0x14 */
    __vo uint32_t AHB3RSTR;       /* 0x18 */

    uint32_t RESERVED0;           /* 0x1C */

    __vo uint32_t APB1RSTR;       /* 0x20 */
    __vo uint32_t APB2RSTR;       /* 0x24 */

    uint32_t RESERVED1[2];        /* 0x28 - 0x2C */

    __vo uint32_t AHB1ENR;        /* 0x30 */
    __vo uint32_t AHB2ENR;        /* 0x34 */
    __vo uint32_t AHB3ENR;        /* 0x38 */

    uint32_t RESERVED2;           /* 0x3C */

    __vo uint32_t APB1ENR;        /* 0x40 */
    __vo uint32_t APB2ENR;        /* 0x44 */

    uint32_t RESERVED3[2];        /* 0x48 - 0x4C */

    __vo uint32_t AHB1LPENR;      /* 0x50 */
    __vo uint32_t AHB2LPENR;      /* 0x54 */
    __vo uint32_t AHB3LPENR;      /* 0x58 */

    uint32_t RESERVED4;           /* 0x5C */

    __vo uint32_t APB1LPENR;      /* 0x60 */
    __vo uint32_t APB2LPENR;      /* 0x64 */

    uint32_t RESERVED5[2];        /* 0x68 - 0x6C */

    __vo uint32_t BDCR;            /* 0x70 */
    __vo uint32_t CSR;             /* 0x74 */

    uint32_t RESERVED6[2];         /* 0x78 - 0x7C */

    __vo uint32_t SSCGR;           /* 0x80 */
    __vo uint32_t PLLI2SCFGR;      /* 0x84 */
    __vo uint32_t PLLSAICFGR;      /* 0x88 */
    __vo uint32_t DCKCFGR;         /* 0x8C */
    __vo uint32_t CKGATENR;        /* 0x90 */
    __vo uint32_t DCKCFGR2;       /* 0x94 */

} RCC_RegDef_t;


/*
 * EXTI register definition
 */
typedef struct
{
    __vo uint32_t IMR;             /* 0x00 - Interrupt mask */
    __vo uint32_t EMR;             /* 0x04 - Event mask */
    __vo uint32_t RTSR;            /* 0x08 - Rising trigger */
    __vo uint32_t FTSR;            /* 0x0C - Falling trigger */
    __vo uint32_t SWIER;            /* 0x10 - Software interrupt */
    __vo uint32_t PR;              /* 0x14 - Pending register */

} EXTI_RegDef_t;


/*
 * SYSCFG register definition
 */
typedef struct
{
    __vo uint32_t MEMRMP;          /* 0x00 */
    __vo uint32_t PMC;             /* 0x04 */
    __vo uint32_t EXTICR[4];       /* 0x08 - 0x14 */

    uint32_t RESERVED1[2];         /* 0x18 - 0x1C */

    __vo uint32_t CMPCR;           /* 0x20 */

    uint32_t RESERVED2[2];         /* 0x24 - 0x28 */

    __vo uint32_t CFGR;            /* 0x2C */

} SYSCFG_RegDef_t;


/***************************************************************
 * Peripheral definitions
 ***************************************************************/

#define GPIOA       ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB       ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC       ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD       ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE       ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF       ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG       ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH       ((GPIO_RegDef_t *)GPIOH_BASEADDR)

#define RCC         ((RCC_RegDef_t *)RCC_BASEADDR)

#define EXTI        ((EXTI_RegDef_t *)EXTI_BASEADDR)

#define SYSCFG      ((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)


/***************************************************************
 * GPIO clock enable macros
 ***************************************************************/

#define GPIOA_PCLK_EN()       (RCC->AHB1ENR |= (1U << 0))
#define GPIOB_PCLK_EN()       (RCC->AHB1ENR |= (1U << 1))
#define GPIOC_PCLK_EN()       (RCC->AHB1ENR |= (1U << 2))
#define GPIOD_PCLK_EN()       (RCC->AHB1ENR |= (1U << 3))
#define GPIOE_PCLK_EN()       (RCC->AHB1ENR |= (1U << 4))
#define GPIOF_PCLK_EN()       (RCC->AHB1ENR |= (1U << 5))
#define GPIOG_PCLK_EN()       (RCC->AHB1ENR |= (1U << 6))
#define GPIOH_PCLK_EN()       (RCC->AHB1ENR |= (1U << 7))


/***************************************************************
 * GPIO clock disable macros
 ***************************************************************/

#define GPIOA_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 4))
#define GPIOF_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 5))
#define GPIOG_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 6))
#define GPIOH_PCLK_DI()       (RCC->AHB1ENR &= ~(1U << 7))


/***************************************************************
 * GPIO peripheral reset macros
 ***************************************************************/

#define GPIOA_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 0); \
                                   RCC->AHB1RSTR &= ~(1U << 0); } while(0)

#define GPIOB_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 1); \
                                   RCC->AHB1RSTR &= ~(1U << 1); } while(0)

#define GPIOC_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 2); \
                                   RCC->AHB1RSTR &= ~(1U << 2); } while(0)

#define GPIOD_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 3); \
                                   RCC->AHB1RSTR &= ~(1U << 3); } while(0)

#define GPIOE_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 4); \
                                   RCC->AHB1RSTR &= ~(1U << 4); } while(0)

#define GPIOF_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 5); \
                                   RCC->AHB1RSTR &= ~(1U << 5); } while(0)

#define GPIOG_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 6); \
                                   RCC->AHB1RSTR &= ~(1U << 6); } while(0)

#define GPIOH_REG_RESET()     do { RCC->AHB1RSTR |=  (1U << 7); \
                                   RCC->AHB1RSTR &= ~(1U << 7); } while(0)


/***************************************************************
 * SYSCFG clock
 *
 * APB2ENR bit 14 = SYSCFG clock enable
 ***************************************************************/

#define SYSCFG_PCLK_EN()      (RCC->APB2ENR |= (1U << 14))
#define SYSCFG_PCLK_DI()      (RCC->APB2ENR &= ~(1U << 14))


#endif /* INC_STM32F446XX_H_ */

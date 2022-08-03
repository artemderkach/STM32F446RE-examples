#include <stdint.h>

#define PERIPH_BASE         0x40000000UL // stm32f446xx.h - Peripheral base address
#define AHB1PERIPH_OFFSET   0x00020000UL // Advanced Microcontroller Bus 1 offset

#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET) // stm32f446xx.h - Advanced Microcontroller Bus 1 base

#define GPIOA_OFFSET        0x0000UL
#define GPIOA_BASE          (AHB1PERIPH_BASE + GPIOA_OFFSET) // stm32f446xx.h

#define RCC_OFFSET          0x00003800UL // Reset clock control offset
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET) // stm32f446xx.h - Reset clock control base

#define AHB1ENR_OFFSET      0x30UL // stm32f446xx.h - RCC->AHB1ENR
#define RCC_AHB1ENR         (*(volatile unsigned int *) (RCC_BASE + AHB1ENR_OFFSET))

#define MODER_OFFSET        0x00UL
#define GPIOA_MODER         (*(volatile unsigned int *) (GPIOA_BASE + MODER_OFFSET))

#define ODR_OFFSET          0x14UL
#define GPIOA_ODR           (*(volatile unsigned int *) (GPIOA_BASE + ODR_OFFSET))

#define PIN5                (1U<<5)
#define LED_PIN             PIN5

#define GPIOAEN             (1U<<0)

typedef struct {
    volatile __uint32_t MODER;    // GPIO port mode register,               Address offset: 0x00
    volatile __uint32_t OTYPER;   // GPIO port output type register,        Address offset: 0x04
    volatile __uint32_t OSPEEDR;  // GPIO port output speed register,       Address offset: 0x08
    volatile __uint32_t PUPDR;    // GPIO port pull-up/pull-down register,  Address offset: 0x0C
    volatile __uint32_t IDR;      // GPIO port input data register,         Address offset: 0x10
    volatile __uint32_t ODR;      // GPIO port output data register,        Address offset: 0x14
    volatile __uint32_t BSRR;     // GPIO port bit set/reset register,      Address offset: 0x18
    volatile __uint32_t LCKR;     // GPIO port configuration lock register, Address offset: 0x1C
    volatile __uint32_t AFR[2];   // GPIO alternate function registers,     Address offset: 0x20-0x24
} GPIO_TypeDef;

typedef struct {
    volatile __uint32_t CR;           // RCC clock control register,                                  Address offset: 0x00
    volatile __uint32_t PLLCFGR;      // RCC PLL configuration register,                              Address offset: 0x04
    volatile __uint32_t CFGR;         // RCC clock configuration register,                            Address offset: 0x08
    volatile __uint32_t CIR;          // RCC clock interrupt register,                                Address offset: 0x0C
    volatile __uint32_t AHB1RSTR;     // RCC AHB1 peripheral reset register,                          Address offset: 0x10
    volatile __uint32_t AHB2RSTR;     // RCC AHB2 peripheral reset register,                          Address offset: 0x14
    volatile __uint32_t AHB3RSTR;     // RCC AHB3 peripheral reset register,                          Address offset: 0x18
             __uint32_t RESERVED0;    // Reserved,                                                    Address offset: 0x1C
    volatile __uint32_t APB1RSTR;     // RCC APB1 peripheral reset register,                          Address offset: 0x20
    volatile __uint32_t APB2RSTR;     // RCC APB2 peripheral reset register,                          Address offset: 0x24
             __uint32_t RESERVED1[2]; // Reserved,                                                    Address offset: 0x28-0x2C
    volatile __uint32_t AHB1ENR;      // RCC AHB1 peripheral clock register,                          Address offset: 0x30
    volatile __uint32_t AHB2ENR;      // RCC AHB2 peripheral clock register,                          Address offset: 0x34
    volatile __uint32_t AHB3ENR;      // RCC AHB3 peripheral clock register,                          Address offset: 0x38
             __uint32_t RESERVED2;    // Reserved,                                                    Address offset: 0x3C
    volatile __uint32_t APB1ENR;      // RCC APB1 peripheral clock enable register,                   Address offset: 0x40
    volatile __uint32_t APB2ENR;      // RCC APB2 peripheral clock enable register,                   Address offset: 0x44
             __uint32_t RESERVED3[2]; // Reserved,                                                    Address offset: 0x48-0x4C
    volatile __uint32_t AHB1LPENR;    // RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
    volatile __uint32_t AHB2LPENR;    // RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
    volatile __uint32_t AHB3LPENR;    // RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
             __uint32_t RESERVED4;    // Reserved,                                                    Address offset: 0x5C
    volatile __uint32_t APB1LPENR;    // RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
    volatile __uint32_t APB2LPENR;    // RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
             __uint32_t RESERVED5[2]; // Reserved,                                                    Address offset: 0x68-0x6C
    volatile __uint32_t BDCR;         // RCC Backup domain control register,                          Address offset: 0x70
    volatile __uint32_t CSR;          // RCC clock control & status register,                         Address offset: 0x74
             __uint32_t RESERVED6[2]; // Reserved,                                                    Address offset: 0x78-0x7C
    volatile __uint32_t SSCGR;        // RCC spread spectrum clock generation register,               Address offset: 0x80
    volatile __uint32_t PLLI2SCFGR;   // RCC PLLI2S configuration register,                           Address offset: 0x84
    volatile __uint32_t PLLSAICFGR;   // RCC PLLSAI configuration register,                           Address offset: 0x88
    volatile __uint32_t DCKCFGR;      // RCC Dedicated Clocks configuration register,                 Address offset: 0x8C
    volatile __uint32_t CKGATENR;     // RCC Clocks Gated ENable Register,                            Address offset: 0x90
    volatile __uint32_t DCKCFGR2;     // RCC Dedicated Clocks configuration register 2,               Address offset: 0x94
} RCC_TypeDef;

#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define GPIOA   ((GPIO_TypeDef *) GPIOA_BASE)

int main(void) {
    // Enable clock access
    RCC->AHB1ENR |= GPIOAEN;

    // set PA5 as output pin
    GPIOA->MODER |=  (1U<<10); // 10 pin to 1
    GPIOA->MODER &= ~(1U<<11); // 11 pin to 0


    while (1) {
        // toggle pin5 to turn on/off the LED
        GPIOA->ODR ^= LED_PIN;

        for (int i = 0; i < 100000; ++i) {}
    }
}
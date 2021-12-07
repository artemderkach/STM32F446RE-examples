#define PERIPH_BASE         0x40000000UL // stm32f446xx.h - Peripheral base address
#define AHB1PERIPH_OFFSET   0x00020000UL // Advanced Microcontroller Bus 1 offset

#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET) // stm32f446xx.h - Advanced Microcontroller Bus 1 base

#define GPIOA_OFFSET        0x0000UL
#define GPIOA_BASE          (PERIPH_BASE + GPIOA_OFFSET) // stm32f446xx.h

#define RCC_OFFSET          0x00003800 // Reset clock control offset
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET) // stm32f446xx.h - Reset clock control base

#define AHB1ENR_OFFSET      0x30UL // stm32f446xx.h - RCC->AHB1ENR
#define RCC_AHB1ENR         (*(volatile unsigned int *) (RCC_BASE + AHB1ENR_OFFSET))

#define MODER_OFFSET        0U
#define GPIOA_MODER         (*(volatile unsigned int *) (GPIOA_BASE + MODER_OFFSET))

#define ODR_OFFSET          0x14UL
#define GPIOA_ODR           (*(volatile unsigned int *) (GPIOA_BASE + ODR_OFFSET))

#define PIN5                (1U<<5)
#define LED_PIN             PIN5

#define GPIOAEN             (1U<<0)

int SystemInit(void) {
    return 0;
}

int main(void) {
    // 1. Enable clock access
    RCC_AHB1ENR |= GPIOAEN;
    // 2. set PA5 as output pin
    GPIOA_MODER |=  (1U<<10); // 10 pin to 1
    GPIOA_MODER &= ~(1U<<11); // 11 pin to 0

    while(1) {
        GPIOA_ODR |= LED_PIN;
        // for (int i=0;i<100000;i+=1) {}
    }
}
#include <stdint.h>

#include "lib/stm32f446xx.h"

#define PIN5    (1U<<5)
#define GPIOAEN (1U<<0)

#define PIN13   (1U<<13)
#define GPIOCEN (1U<<2)

// the user button is connected to the I/O PC13 (pin 2) of the STM32
// microcontroller.

int main(void) {
    // Enable clock access
    RCC->AHB1ENR |= GPIOAEN;
    RCC->AHB1ENR |= GPIOCEN;

    // set PA5 as output pin
    GPIOA->MODER |=  (1U<<10); // 10 pin to 1
    GPIOA->MODER &= ~(1U<<11); // 11 pin to 0

    // set PC13 as input pin. Default state (can skip this step)
    GPIOC->MODER &= ~(1U<<26); // 26 pin to 0
    GPIOC->MODER &= ~(1U<<27); // 27 pin to 0

    while (1) {
        if (GPIOC->IDR & PIN13) {
            GPIOA->ODR ^= PIN5;
            for (int i = 0; i < 100000; ++i) {}
        }
    }
}
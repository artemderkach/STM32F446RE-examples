#include <stdint.h>

#include "lib/stm32f446xx.h"

#define PIN5                (1U<<5)
#define GPIOAEN             (1U<<0)

int main(void) {
    // Enable clock access
    RCC->AHB1ENR |= GPIOAEN;

    // set PA5 as output pin
    GPIOA->MODER |=  (1U<<10); // 10 pin to 1
    GPIOA->MODER &= ~(1U<<11); // 11 pin to 0


    while (1) {
        GPIOA->BSRR = PIN5;
        for (int i = 0; i < 100000; ++i) {}

        GPIOA->BSRR = (1U<<21);
        for (int i = 0; i < 100000; ++i) {}
    }
}
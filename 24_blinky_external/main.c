#include "lib/stm32f446xx.h"

int main(void) {
    // Enable clock access
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // set PA5 as output pin
    GPIOA->MODER |=  GPIO_MODER_MODE5_0; // 10 pin to 1
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1; // 11 pin to 0


    while (1) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        for (int i = 0; i < 100000; ++i) {}

        GPIOA->BSRR = GPIO_BSRR_BR5;
        for (int i = 0; i < 100000; ++i) {}
    }
}
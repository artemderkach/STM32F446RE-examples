#include <stdint.h>

#include "lib/stm32f446xx.h"

int main(void) {
    // GPIO
    // Enable clock access
    RCC->APB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 Alternate function mode (10)
    GPIOA->MODER |=  GPIO_MODER_MODER2_1;
    GPIOA->MODER &= ~GPIO_MODER_MODER2_0;

    // Select alternate function AF7 (0111) for USART2
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_0;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_1;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_2;
    GPIOA->AFR[0] &= &GPIO_AFRL_AFRL2_3;

    // UART
    // Enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Configure baud rate


    // Configure transfer direction
    USART2->CR1 |= USART_CR1_TE;

    // Enable UART module
    USART2->CR1 |= USART_CR1_UE;

    while (1) {

    }
}
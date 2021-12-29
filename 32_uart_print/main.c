#include <stdio.h>
#include "lib/stm32f446xx.h"

#define freq 16000000U // default clock frequency for APB1
#define baud 115200U // default baud rate

int _write(int file, char *ptr, int len){
    (void)file;
    int i;
    for (i =0; i<len; i++){
        while(!(USART2->SR & USART_SR_TXE)){}

        // Write to transmit data register
        USART2->DR = (*ptr++ & 0xFF);
    }
    return len;
}

int main(void) {
    // GPIO
    // Enable clock access
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 Alternate function mode ([5:4] bit is [1:0])
    GPIOA->MODER &= ~GPIO_MODER_MODER2_0; // 4-th bit
    GPIOA->MODER |=  GPIO_MODER_MODER2_1; // 5-th bit

    // Select alternate function AF7 (0111) for USART2
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_0;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_1;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFRL2_2;
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2_3;

    // UART
    // Enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Configure baud rate
    USART2->BRR = ((freq + (baud/2U))/baud);

    // Configure transfer direction
    USART2->CR1 = USART_CR1_TE;

    // Enable UART module
    USART2->CR1 |= USART_CR1_UE;

    while (1) {
        printf("Hello There\n\r");
    }
}
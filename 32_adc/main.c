#include <stdint.h>

#include "lib/stm32f446xx.h"

#define freq 16000000U // default clock frequency for APB1
#define baud 1152000U // default baud rate

void init_adc(void);
void init_uart(void);

int main(void) {

    uint32_t val;

    init_adc();
    init_uart();

    while (1) {
        // start adc conversion
        ADC1->CR2 |= ADC_CR2_SWSTART;

        // wait for ADC conversion to be complete
        while (ADC1->SR & ADC_SR_EOC) {}

        // read converted result
        val = ADC1->DR;

        while(!(USART2->SR & USART_SR_TXE)) {}
        USART2->DR = ('E' & 0xFF);
    }
}

void init_adc(void) {
    // GPIO
    // Enable clock access
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 analog function mode ([3:2] bit is [1:1])
    GPIOA->MODER |= GPIO_MODER_MODER1_0; // 2-nd bit
    GPIOA->MODER |= GPIO_MODER_MODER1_1; // 3-rd bit

    // ADC
    // Enable clock access
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->SQR3 |=  ADC_SQR3_SQ1_0;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1_1;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1_2;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1_3;

    ADC1->SQR1 &= ~ADC_SQR1_L_0;
    ADC1->SQR1 &= ~ADC_SQR1_L_1;
    ADC1->SQR1 &= ~ADC_SQR1_L_2;
    ADC1->SQR1 &= ~ADC_SQR1_L_3;

    // enable ADC module
    ADC1->CR2 |= ADC_CR2_ADON;
}

void init_uart(void) {
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
}
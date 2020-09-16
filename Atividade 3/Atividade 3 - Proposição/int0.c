#include <stdint.h>
#include "stm32f103xb.h"
#include "cmsis_gcc.h"

#define LED_PORT GPIOC
#define LED_PINNBR 13

void EXTI0_IRQHandler() {
}

int main(void) {
    /* Habilitando o relógio da porta C para o pino EXTI0 (Porta A) e 
       configura bit 13 da porta GPIOC como input pull-up/pull-down 
       para o pino EXTI0. Veja Seções 7.3 e 9.2 do Manual de Referência */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);
    GPIOA->CRL &= ~GPIO_CRL_CNF0_Msk;
    GPIOA->CRL |= (GPIO_CRL_CNF0_1);
    
    /* Habilitando a funcionalidade de EXTI, Seções 10.3 e  do Manual de Referência */
    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->FTSR |= EXTI_FTSR_TR0;
    AFIO->EXTICR[0] = 0;
    
    /* Habilitando e especificando a prioridade da interrupção de interesse.
       Veja Seção 10.3 do Manual de Referência e Seção 4.3 do Manual de Programação
       do Stm32f103 */
    EXTI->IMR |= EXTI_IMR_MR0;
#if 0
    NVIC->ISER[EXTI0_IRQn >> 5] = (1U << (EXTI0_IRQn & 0x1F));
    /* O campo IP abaixo na realidade se chama IPR no Manual de Referência */
    NVIC->IP[EXTI0_IRQn] |= (0x4 << 4); /* 0x4 é prioridade média */
#endif

    /* Habilita interrupçoes globalmente */
    __enable_irq();
    
    /* Habilitando o relógio da porta C para o led e configura bit 13
       da porta GPIOC como output 10 MHz para o led */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    LED_PORT->CRH &= ~GPIO_CRH_MODE13_Msk;
    LED_PORT->CRH |= (GPIO_CRH_MODE13_0);
    LED_PORT->BSRR = (1 << LED_PINNBR);

    while (1) {
        while (EXTI->PR & EXTI_PR_PR0 == 0)
            ;
        EXTI->PR |= EXTI_PR_PR0;

        if (GPIOA->IDR & 1)
            LED_PORT->BRR = (1 << LED_PINNBR);
        else
            LED_PORT->BSRR = (1 << LED_PINNBR);
    }

    return 0;
}

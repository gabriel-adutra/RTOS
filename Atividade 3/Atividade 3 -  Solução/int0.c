#include <stdint.h>
#include "stm32f103xb.h"
#include "cmsis_gcc.h"

#define LED_PORT GPIOC
#define LED_PINNBR 13

void EXTI0_IRQHandler() {
  EXTI->PR |= (1<<0);                           // clear pending interrupt

  if (GPIOA->IDR & 1)
    LED_PORT->BRR = (1 << LED_PINNBR);       // switch off LED
  else
    LED_PORT->BSRR = (1 << LED_PINNBR);       // switch on  LED
}

int main(void) {
    /* Habilitando o relógio da porta C para o pino EXTI0 (Porta A) e
       configura bit 13 da porta GPIOC como input pull-up/pull-down
       para o pino EXTI0. Veja Seções 7.3 e 9.2 do Manual de Referência */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); // ...0001x1
    // RCC->APB2ENR |= (1<<2) | (1<<0);
    GPIOA->CRL &= ~GPIO_CRL_CNF0_Msk; // [3] = 0
    GPIOA->CRL |= (GPIO_CRL_CNF0_1); // [4] = 1

    /* Habilitando a funcionalidade de EXTI, Seções 10.3 e  do Manual de Referência */
    EXTI->RTSR |= EXTI_RTSR_TR0; // Rising trigger enabled
    EXTI->FTSR |= EXTI_FTSR_TR0; // Falling trigger enabled
    AFIO->EXTICR[0] = 0; // Enable interrupt from port A (...0000)

    /* Habilitando e especificando a prioridade da interrupção de interesse.
       Veja Seção 10.3 do Manual de Referência e Seção 4.3 do Manual de Programação
       do Stm32f103 */
    EXTI->IMR |= EXTI_IMR_MR0;

#if 1
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
    
 	//Nada a declarar
      
    }

    return 0;
}

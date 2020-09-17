/* Necessário para funções e macros básicas */
#include <stdint.h>
#include "stm32f103xb.h"
#include "cmsis_gcc.h"

/* Consante definindo período da onda quadrada relacionada à
   inensidade do led.  Não pode ser maior do que 255 */
#define PERIODO 100
/* Número de pulsos da onda quadrada com o ciclo de trabalho fixo */
#define QTDE_PULSOS 10

/* Função implementado delay múltiplo de 10 microsegundos */
void delay_dezenas_us(uint16_t dezenas) {
    int16_t i;
    uint16_t j;

    for (j=0; j<dezenas; j++)
        for (i=10; i>=0; i--) {
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
        }
}

/* Variável global representando quão rápido a onda triangular cresce
   (ou decresce).  Observe o uso de volatile abaixo.  Caso não
   entenda, pergunte ao professor */
volatile uint8_t passo = 1;

/* Implementação de uma onda triangular variando de 0 a PERIODO */
uint8_t onda_triangular(void) {
    static int8_t valor_atual = 0;
    static uint8_t crescente = 1;

    if (crescente)
        valor_atual += passo;
    else
        valor_atual -= passo;

    if (valor_atual > PERIODO) {
        valor_atual = PERIODO;
        crescente = 0;
    } else if (valor_atual < 0) {
        valor_atual = 0;
        crescente = 1;
    }

    return valor_atual;
}


/* A função main() implementa uma onda digital quadrada com o ciclo de
   trabalho variando de acordo com uma função triangular.  Use o valor
   da onda para acender ou apagar o led que está no 6º pino da porta
   B. */
int main(void) {
    uint8_t ativo;
    uint8_t i;

    /* Inicialize aqui o que for necessário para o EXTI0 */

    /* Faça a configuração do que for necessário aqui */
    /* Habilita interrupçoes globalmente */
    /* Habilitando o relógio da porta C para o led e configura bit 13
       da porta GPIOC como output 10 MHz para o led */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    __enable_irq();

    /* Implementação de uma onda quadrada com ciclo de trabalho
       variável. O ciclo de trabalho varia a cada QTDE_PULSOS pulsos
       da onda quadrada */
    while (1) {
        ativo = onda_triangular();
        for (i=0; i<QTDE_PULSOS; i++) {
            /* Parte ativa da onda quadrada */
            delay_dezenas_us(ativo);
            /* Parte inativa da onda quadrada */
            delay_dezenas_us(PERIODO - ativo);
        }
    }

    return 0;
}

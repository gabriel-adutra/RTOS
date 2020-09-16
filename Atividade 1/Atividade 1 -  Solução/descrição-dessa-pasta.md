

1 -	Nessa pasta você encontra a solução para o problema da atividade um, 
	descrito na pasta "Atividade 1 - Proposição".
	A modificação feita se encontra no arquivo int0.c.
	O problema foi solucionado utilizando o STM32, portanto o código faz referência a esse 		microcontrolador.
	Abaixo segue um breve resumo do que são interrupções.
	
	
INTERRUPÇÕES:

1 - 	Interrupções são um mecanismo que permite o MCU ser interrompido quando o evento ocorre
2 -	A vantagem é que o MCU pode fazer outras coisas enquanto o evento não ocorre
3 - 	A desvantagem é que a interrupção irá executar concorrentemente com o prorgrama
4 - 	Outra desvantagem é que leva um certo tempo para o MCU parar o que estava fazendo e tratar a     		interrupção
	


PARA COMPILAR E GRAVAR OS ARQUIVOS NO STM32 ABRA O TERMINAL NESSA PASTA E UTILIZE OS SEGUINTES COMANDOS:

arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb startup_stm32f103xb.s
arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -O3 int0.c
arm-none-eabi-gcc -T stm32f103xb.ld -nostartfiles -o int0.elf int0.o startup_stm32f103xb.o
arm-none-eabi-objcopy -S -O ihex int0.elf int0.hex
(QUANDO USAR O CONVERSOR USB-TTL) stm32flash -w int0.hex /dev/ttyUSB0
(QUANDO USAR O PROGRAMADOR STLINK)   st-flash --format ihex write int0.hex

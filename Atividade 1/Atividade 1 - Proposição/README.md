##	Descrição dessa pasta

*	Essa pasta contém o código, fornecido pelo professor, de um 
	programa que utiliza polling para detectar mudança de nível
	lógico em um pino do microcontrolador.
	
*	O objetivo dessa atividade é converter esse programa, que utiliza polling, em um
	programa que utilize interrupções cuja finalidade é a mesma supracitada.

*	Esta pasta contém apenas o código original, ou seja, utilizando polling. 
	Para acessar o código modificado que utiliza interrupções, acesse a pasta
	"Atividade 1 Solução". Lá você encontrará uma breve descrição sobre interrupções. 

### Polling:

*	Polling consiste de um loop cuja condição de saída é a ocorrência de um evento.
*	Polling é simples de implementar pois está no fluxo sequencial do programa.
*	A desvantagem é que, se o evento não é frequente, o microcontrolador perde muito tempo fazendo o polling.
*	Se colocarmos instruções entre os momentos de polling, podemos criar jitter.


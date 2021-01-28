# Trabalho 1 - Sistemas Operacionais

Gabriel Martins Machado Christo - 117217732

Vinicius Lima Medeiros - 117097920

Objetivo: Desenvolver um simulador de escalonamento de processos utilizando a estratégia de seleção Round Robin com Multi Level Feedback Queue

### Arquitetura do Simulador

Constants - Definição de enumerações e valores estáticos utilizados pelo simulador

Process - Métodos referentes à estrutura de processos

IO - Métodos referentes à estrutura de i/o

CPU - Simulação dos ciclos de execução da CPU e algoritmos de escalonamento. Centraliza as filas e lista de processos

Queue - Estrutura de dados de fila

### Premissas do Simulador

- 2 Filas (baixa e alta prioridade) para execução dos processos utilizando estratégia round robin

- Mesmo quantum para ambas as filas de processos, com quantum definido no arquivo constants.h

- 3 filas para execução de IO utilizando estratégia FCFS (uma fila para cada tipo de IO)

- Número de processos definido estaticamente no arquivo constants.h

- Valores de tempo de chegada e tempo de serviço aleatórios para cada processo

- Ordem de entrada dos processos nas filas
	- Processos novos: fila de alta prioridade
	- Processos voltando do IO: fila de baixa prioridade para disco e alta prioridade para impressora e fita magnética
	- Processos que sofreram preempção: fila de baixa prioridade
	




	

### TODO

- oque deve ser feito a cada ciclo
	
	- detectar processos voltando de io. voltar pra fila de acordo com tipo de IO. mudar estado do processo para Ready
	
	- adicionar processos novos na fila de alta prioridade (se estiver no arrival time do processo)
	
	- checar se processo executando vai iniciar IO. Caso sim alterar estado para Blocked e enviar processo para fila de IO. resetar quantum desse processo
	
	- verificar se processo Running finalizou. mudar estado para finished e resetar quantum. verificar novo processo pra ser executado
	
	- decrementar burstTime do processo Running
	
	- verificar quantumCounter do processo e aplicar preempcao se necessario (processo interropido vai pra fila de baixa prioridade). executar novo processo.

- liberar toda memoria alocada

- metodo para detectar novo processo a ser executado (atualizar variavel crrtProcess da cpu e atualizar status)


- mudar nome cpu para scheduler ?






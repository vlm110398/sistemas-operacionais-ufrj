# Trabalho 1 - Sistemas Operacionais

Gabriel Martins Machado Christo - 117217732

Vinicius Lima Medeiros - 117097920

Objetivo: Desenvolver um simulador de escalonamento de processos usando a estratégia de seleção Round Robin com Feedback Queue

### Arquitetura do Simulador

Constants - definição de enumerações e valores estáticos utilizados pelo simulador

Process - métodos referentes à estrutura de processos

IO - métodos referentes à estrutura de i/o

CPU - simulação dos ciclos de máquina da CPU e algoritmos de escalonamento

Queue - estrutura de dados de fila


### Premissas

- Ordem de entrada
	- Processos novos: fila de alta prioridade
	- Processos voltando do io para fila de execução: depende do io
	- Processos que sofreram preempção: fila de baixa prioridade

	
- 2 Filas de prioridade para execução dos processos (round robin)

- 3 filas para execução de io (FCFS)

- mesmo quantum para filas de processos
	

### TODO

- oque deve ser feito a cada ciclo
	- checar todos processos finalizaram
	- processos voltando de io (voltar pra fila)












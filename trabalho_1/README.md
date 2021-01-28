# Trabalho 1 - Sistemas Operacionais

Gabriel Martins Machado Christo - 117217732

Vinicius Lima Medeiros - 117097920

Objetivo: Desenvolver um simulador de escalonamento de processos utilizando a estratégia de seleção Round Robin com Multi Level Feedback Queue

### Arquitetura do Simulador

Constants - definição de enumerações e valores estáticos utilizados pelo simulador

Process - métodos referentes à estrutura de processos

IO - métodos referentes à estrutura de i/o

CPU - simulação dos ciclos de execução da CPU e algoritmos de escalonamento

Queue - estrutura de dados de fila

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
	- processos voltando de io (voltar pra fila)

- liberar toda memoria alocada










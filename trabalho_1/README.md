# Trabalho 1 - Sistemas Operacionais

Gabriel Martins Machado Christo - 117217732
Vinicius Lima Medeiros - 

Objetivo: Desenvolver um simulador de escalonamento de processos usando a estratégia de seleção Round Robin com Feedback


### Arquitetura do Simulador

Constants - definição de enumerações e valores estáticos utilizados pelo simulador

Process - métodos referentes à estrutura de processos

IO - métodos referentes à estrutura de i/o

CPU - simulação dos ciclos de máquina da CPU e algoritmos de escalonamento

Queue - estrutura de dados de fila


### Premissas

- Ordem de entrada
	- Processos novos: fila de alta prioridade
	- Processos voltando do io: depende do io
	- Processos que sofreram preempção: fila de baixa prioridade


### TODO

- inicializar N processos com tempo de serviço e duração de io aleatorios
- 2 filas pra cpu (low e high priority)
- 3 filas para io
- oque deve ser feito a cada ciclo?


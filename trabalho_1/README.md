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

- Tempo de serviço de IO definido aleatoriamente no momento da criação de seu processo pai

- Número de processos definido estaticamente no arquivo constants.h

- Valores de tempo de chegada e tempo de serviço aleatórios para cada processo

- Ordem de entrada dos processos nas filas
	- Processos novos: fila de alta prioridade
	- Processos voltando do IO: fila de baixa prioridade para disco e alta prioridade para impressora e fita magnética
	- Processos que sofreram preempção: fila de baixa prioridade
	
- Após finalizar IO processo retorna para fila de prioridades (de acordo com tipo de IO) para ser executado na próxima iteração


### Ordem de execução do simulador

- Inicialização da estruturas
- Simulação (loop principal)
	- checagem de processos iniciando operação de IO
		- se estiver iniciando processo sai da fila de prioridade e vai pra fila de IO
		- processo vai pra estado bloqueado
	- executando processo
		- verificar processo com maior prioridade
		- executa/finaliza/aplica preempção (round robin) no processo obtido
		- em caso de finalização/preempção do processo obtido já executamos o próximo processo
	- executa operações nas fila de IO (FCFS)
	- insere novos processo na fila de alta prioridade
		- baseado no tempo de chegada
		- entra na fila com estado pronto
	- checagem de processos com IO finalizado
		- IO de disco finalizado volta para fila de baixa prioridade
		- IO de fita magnética finalizado volta para fila de alta prioridade
		- IO de impressora finalizado volta para fila de alta prioridade
		- volta pra fila de prioridade com estado pronto
	- mostra o estado de todas as fila ao final dessa iteração
- mostra resultados da simulação
- Liberação da memória alocada
	

### TODO


	metodos:
		advance to next process
		handle finished process
		
	handle finished process quando finalizar io?
	
	while na hora de verificar missingcyclestofinish?
	
	mudar nome cpu para scheduler?

	metodo free all memory







#ifndef CONSTANTS_H
#define CONSTANTS_H

#define QUANTUM 5

#define MAX_PROCESSES 3
#define MAX_ARRIVAL_TIME 10
#define MAX_BURST_TIME 10
#define MAX_CYCLES 50

#define MAX_IO_BURST_TIME 20
#define MAX_IO_RELATIVE_START 5

#define TRUE 1
#define FALSE 0
#define bool int

typedef enum
{ 
    NOT_STARTED = 0,	// processo nao iniciado
	READY,  			// pronto pra executar
	BLOCKED,			// bloqueado devido io ou preempcao
	RUNNING,			// executando
	FINISHED,			// finalizado
	PROCESS_STATUS_NUMBER
	
} PROCESS_STATUS;

typedef enum
{
    DISK = 0,			// vai pra fila de baixa prioridade (definida duracao de 5 tempos)
	MAGNETIC_TAPE,		// vai pra fila de alta prioridade (definida duracao de 7 tempos)
	PRINTER,			// vai pra fila de alta prioridade (definida duracao de 9 tempos)
	IO_TYPE_NUMBER
	
} IO_TYPE;

typedef enum
{
	LOW_PRIORITY_QUEUE = 0, 	// fila de baixa prioridade
	HIGH_PRIORITY_QUEUE, 		// fila de alta prioridade
	DISK_QUEUE,					// fila de io de disco
	MAGNETIC_TAPE_QUEUE,        // fila de io de fita magnetica
	PRINTER_QUEUE,				// fila de io da impressora  
	QUEUE_TYPE_NUMBER
	
} QUEUE_TYPE;


#endif

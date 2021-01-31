#ifndef CONSTANTS_H
#define CONSTANTS_H

#define QUANTUM 3

#define MAX_PROCESSES 7
#define MAX_ARRIVAL_TIME 7
#define MAX_BURST_TIME 6
#define MAX_CYCLES 1000 // avoid infinity loop
#define MAX_IO_BURST_TIME 6

#define TRUE 1
#define FALSE 0
#define bool int

#define BRIGHT_GREEN "\x1b[92m"
#define BRIGHT_CYAN  "\x1b[96m"
#define RESET		 "\x1b[0m"

typedef enum
{ 
    NOT_STARTED = 0,	// processo nao iniciado
	READY,  			// pronto pra executar
	BLOCKED,			// bloqueado devido io ou preempcao
	RUNNING,			// executando
	FINISHED,			// finalizado
	EXECUTION_STATUS_NUMBER
	
} EXECUTION_STATUS;

typedef enum
{
    DISK = 0,			// vai pra fila de baixa prioridade
	MAGNETIC_TAPE,		// vai pra fila de alta prioridade
	PRINTER,			// vai pra fila de alta prioridade
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

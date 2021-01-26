#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_PROCESSES 7
#define QUANTUM 5
#define MAX_CYCLES 1000

typedef enum { 
    NOT_STARTED = 0,	// processo nao iniciado
	READY,  			// pronto pra executar
	BLOCKED,			// bloqueado devido io
	RUNNING,			// executando
	FINISHED			// finalizado
} PROCESS_STATUS;

typedef enum {
    DISK = 0,			// vai pra fila de baixa prioridade (duracao de 5 tempos)
	MAGNETIC_TAPE,		// vai pra fila de alta prioridade (duracao de 7 tempos)
	PRINTER				// vai pra fila de alta prioridade (duracao de 9 tempos)
} IO_TYPE;

typedef enum { 
  LOW_PRIORITY_QUEUE = 0, 	// fila de baixa prioridade
  HIGH_PRIORITY_QUEUE, 		// fila de alta prioridade
  IO_QUEUE,					// fila de io
  RESULT_QUEUE,				// fila com resultado da simulacao
  READY_QUEUE
} QUEUE_TYPE;

typedef enum { 
  IO_ELEMENT = 0,
  PROCESS_ELEMENT
} ELEMENT_TYPE;


#endif

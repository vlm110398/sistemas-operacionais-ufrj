#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_PROCESSES 5
#define QUANTUM 3

typedef enum { 
    NOT_STARTED = 0,
	READY,
	BLOCKED,
	RUNNING,
	FINISHED
} PROCESS_STATUS;

typedef enum {
    DISK = 0,		// goes to low priority queue
	MAGNETIC_TAPE,	// goes to high priority queue
	PRINTER			// goes to high priority queue
} IO_TYPE;

typedef enum { 
  LOW_PRIORITY_QUEUE = 0, 	// fila de baixa prioridade
  HIGH_PRIORITY_QUEUE, 		// fila de alta prioridade
  IO_QUEUE,					// fila de io
  RESULT_QUEUE				// fila com resultado da simulacao
} QUEUE_TYPE;

typedef enum { 
  IO_ELEMENT = 0,
  PROCESS_ELEMENT
} ELEMENT_TYPE;


#endif

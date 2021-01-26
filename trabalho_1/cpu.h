#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include "constants.h"
#include "process.h"
#include "io.h"
#include "queue.h"

typedef struct {
	
	int currentCycle;
	
	process_t* currentProcess;
	
	queue_t* lowPriorityQueue;
	queue_t* highPriorityQueue;
	queue_t* ioQueue;
	queue_t* readyQueue;
	
} cpu_t;



#endif

#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "process.h"
#include "io.h"
#include "queue.h"

typedef struct {
	
	int currentCycle;
	
	process_t* currentProcess;
	process_t** processes;
	
	queue_t* lowPriorityQueue;
	queue_t* highPriorityQueue;
	
	queue_t* ioDiskQueue;
	queue_t* ioPrinterQueue;
	queue_t* ioMagneticTapeQueue;
	
} cpu_t;

// initializes cpu struct
cpu_t* init_cpu(process_t** processes);

// check all processes are at finished status
bool all_process_has_finished(process_t** processes);

// initialize simulation loop
void start_simulation(cpu_t* cpu);

// put new process in cpu



#endif

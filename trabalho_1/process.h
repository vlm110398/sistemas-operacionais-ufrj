#ifndef PROCESS_H
#define PROCESS_H

#include "constants.h"

typedef struct {
    int pid;				// process id
    int ppid;				// parent process id
    PROCESS_STATUS status;	// process current status
    int arrivalTime;		// arrival time
    int burstTime;			// burst time
} process_t;

// initialize a process
process_t* init_process(int arrival, int burst, process_t* parent);

#endif

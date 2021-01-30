#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "io.h"

typedef struct
{
	// ----- Information about process -----
    int pid;				// process id
    int ppid;				// parent process id
	io_t* io;				// io operation of process
    int arrivalTime;		// arrival time
    int burstTime;			// burst time
	
	// ----- Auxiliar variables -----
	PROCESS_STATUS status;		// process current status
	int quantumCounter;     	// slice time counter
	int missingCyclesToFinish;	// missing time to process finishing
	int beginTime;				// current round robin starting time
	int endTime;  				// current round robin finishing time
	bool alreadyInIoQueue;      // the process has already been in IO queue?
	bool alreadyOutIoQueue;		// the process has already been out IO queue?
	
} process_t;

// initialize a process
process_t* init_process(int arrival, int burst, process_t* parent);

// initialize N random processes
process_t** init_random_processes(int processNumber);

// print desired process
void print_process(process_t* process);

// print array of processes
void print_processes(process_t** processes, int size);

// get process current state as string
char* get_string_from_process_status(PROCESS_STATUS status);

#endif

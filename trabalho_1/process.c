#include "process.h"

static int process_counter = 0;

process_t* init_process(int arrival, int burst, process_t* parent)
{
    process_t* p = (process_t*) malloc(sizeof(process_t));
	
	p->pid = process_counter++;
	p->status = NOT_STARTED;
	p->arrivalTime = arrival;
	p->burstTime = burst;
	p->quantumCounter = 0;
	p->io = init_random_io();
	
	if(parent != NULL)
		p->ppid = parent->pid;
    
    return p;
}

process_t** init_random_processes(int processNumber)
{
	process_t** processes = malloc(processNumber * sizeof(process_t));
	
	for(int i = 0; i < processNumber; i++)
	{
		processes[i] = init_process(rand() % MAX_ARRIVAL_TIME, rand() % MAX_BURST_TIME, NULL);
	}
	
	return processes;
}
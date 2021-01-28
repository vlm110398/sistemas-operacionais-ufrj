#include "process.h"

static int process_counter = 0;

process_t* init_process(int arrival, int burst, process_t* parent)
{
    process_t* p = (process_t*) malloc(sizeof(process_t));
	
	p->pid = process_counter++;
	p->status = NOT_STARTED;
	p->arrivalTime = arrival;
	p->burstTime = burst;
	p->missingCyclesToFinish = burst;
	p->quantumCounter = 0;
	p->io = init_random_io();
	p->beginTime = 0;
	p->endTime = 0;
	
	if(parent != NULL)
		p->ppid = parent->pid;
	else p->ppid = -1; // -1 means process has no parent
    
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

void print_process(process_t* process)
{
	printf("PID: %d\t", process->pid);
	printf("PPID: %d\t", process->ppid);
	printf("Status: %s\t", get_string_from_process_status(process->status));
	printf("ArrivalTime: %d\t", process->arrivalTime);
	printf("BurstTime: %d\t", process->burstTime);
	printf("IO Type: %d\t", process->io->type);
	printf("Crrt Begin Time: %d\t", process->beginTime);
	printf("Crrt End Time: %d\n\n", process->endTime);
}

void print_processes(process_t** processes, int size)
{
	for(int i = 0; i < size; i++)
	{
		print_process(processes[i]);
	}
}

char* get_string_from_process_status(PROCESS_STATUS status)
{
	switch(status)
	{
		case READY:
			return "Ready";
		case BLOCKED:
			return "Blocked";
		case RUNNING:
			return "Running";
		case FINISHED:
			return "Finished";
		case NOT_STARTED:
		default:
			return "Not Started";
	}
}

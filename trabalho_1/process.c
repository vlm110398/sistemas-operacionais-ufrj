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
	p->finishedTime = 0;
	
	if(parent != NULL)
		p->ppid = parent->pid;
	else p->ppid = -1; // -1 means process has no parent
    
    return p;
}

process_t** init_random_processes(int processNumber)
{
	process_t** processes = malloc(processNumber * sizeof(process_t*));
	
	for(int i = 0; i < processNumber; i++)
	{
		processes[i] = init_process(rand() % MAX_ARRIVAL_TIME, (rand() % MAX_BURST_TIME) + 1, NULL);
		// defining io relative start (must be minor than process burst time and higher than zero)
		processes[i]->io->relativeStart = (rand() % processes[i]->burstTime) + 1;
	}
	
	return processes;
}

void print_process(process_t* process)
{
	printf("PID:" BRIGHT_GREEN " %d " RESET, process->pid);
	printf("PPID:" BRIGHT_GREEN " %d " RESET, process->ppid);
	printf("Status:" BRIGHT_GREEN " %s\t" RESET, get_string_from_execution_status(process->status));
	printf("Arrival:" BRIGHT_GREEN " %d " RESET, process->arrivalTime);
	printf("Burst:" BRIGHT_GREEN " %d " RESET, process->burstTime);
	printf("Remaining Cycles:" BRIGHT_GREEN " %d " RESET, process->missingCyclesToFinish);
	printf("IO Relative Start:" BRIGHT_GREEN " %d " RESET, process->io->relativeStart);
	printf("IO Burst:" BRIGHT_GREEN " %d " RESET, process->io->burstTime);
	printf("IO Status:" BRIGHT_GREEN " %s\t" RESET, get_string_from_execution_status(process->io->status));
	printf("IO Type:" BRIGHT_GREEN " %s\n" RESET, get_string_from_io_type(process->io->type));
}

void print_processes(process_t** processes, int size)
{
	for(int i = 0; i < size; i++)
	{
		print_process(processes[i]);
	}
}

char* get_string_from_execution_status(EXECUTION_STATUS status)
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

#include "process.h"

#include <stdlib.h>

static int process_counter = 0;

process_t* init_process(int arrival, int burst, process_t* parent)
{
    process_t* p = (process_t*) malloc(sizeof(process_t));
	
	p->pid = process_counter++;
	p->status = NOT_STARTED;
	p->arrivalTime = arrival;
	p->burstTime = burst;
	
	if(parent != NULL)
		p->ppid = parent->pid;
    
    return p;
}
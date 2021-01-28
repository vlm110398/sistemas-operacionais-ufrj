#include "cpu.h"

cpu_t* init_cpu(process_t** processes)
{
	cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
	
	cpu->currentCycle = 0;
	
	cpu->currentProcess = NULL;
	cpu->processes = processes;
	
	cpu->lowPriorityQueue = init_queue(LOW_PRIORITY_QUEUE);
	cpu->highPriorityQueue = init_queue(HIGH_PRIORITY_QUEUE);
	
	cpu->ioDiskQueue = init_queue(DISK_QUEUE);
	cpu->ioPrinterQueue = init_queue(PRINTER_QUEUE);
	cpu->ioMagneticTapeQueue = init_queue(MAGNETIC_TAPE_QUEUE);
	
	return cpu;
}

bool all_process_has_finished(process_t** processes)
{
	for(int i = 0; i < MAX_PROCESSES; i++)
	{
		if(processes[i]->status != FINISHED) return FALSE;
	}
	return TRUE;
}

void start_simulation(cpu_t* cpu)
{
	// testing print queue
	for(int i = 0; i < MAX_PROCESSES; i++)
		push(cpu->highPriorityQueue, cpu->processes[i]);
	print_queue(cpu->highPriorityQueue);
	
	
	
	while(all_process_has_finished(cpu->processes) == FALSE && cpu->currentCycle < MAX_CYCLES)
	{
		cpu->currentCycle++;
		printf("Current Cycle: %d\n", cpu->currentCycle);
		
		// todo: process logic
		
		// todo: round robin
		//sleep(1);
	}
	
	printf("Simulation finished\n");
}

process_t* get_next_process_to_be_executed(cpu_t* cpu)
{
	// checking high priority queue
	if(cpu->highPriorityQueue->length > 0)
	{
		// getting element from first process at queue
		queue_element_t* e = pop(cpu->highPriorityQueue);
		return e->process;
	}
	
	// checking low priority queue
	if(cpu->lowPriorityQueue->length > 0)
	{
		// getting element from first process at queue
		queue_element_t* e = pop(cpu->lowPriorityQueue);
		return e->process;
	}
	
	// return NULL if there is no process to execute
	return NULL;
}



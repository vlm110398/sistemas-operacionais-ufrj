#include "cpu.h"

cpu_t* init_cpu()
{
	cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
	
	cpu->currentCycle = 0;
	
	cpu->lowPriorityQueue = malloc(sizeof(queue_t));
	cpu->highPriorityQueue = malloc(sizeof(queue_t));
	cpu->ioQueue = malloc(sizeof(queue_t));
	cpu->readyQueue = malloc(sizeof(queue_t));
	
	return cpu;
}
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

bool all_process_has_finished()
{
	return TRUE;
}
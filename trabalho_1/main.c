
#include <stdio.h>
#include <time.h>
#include "constants.h"
#include "queue.h"
#include "cpu.h"

int main(){
	
	// default seed
	srand(1);
	
	process_t** allProcesses = init_random_processes(MAX_PROCESSES);
	print_processes(allProcesses, MAX_PROCESSES);

	cpu_t* cpu = init_cpu(allProcesses);
	
	while(all_process_has_finished() == FALSE)
	{
		cpu->currentCycle++;
		printf("Current Cycle: %d", cpu->currentCycle);
		
		// todo: process logic
		
		// todo: round robin
	}

    return 0;
}
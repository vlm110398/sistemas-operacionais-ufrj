
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
	start_simulation(cpu);

    return 0;
}
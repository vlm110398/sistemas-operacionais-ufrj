#include "cpu.h"

cpu_t* init_cpu(process_t** processes)
{
	cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
	
	cpu->currentCycle = 0;
	
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
	while(all_process_has_finished(cpu->processes) == FALSE && cpu->currentCycle < MAX_CYCLES)
	{	
		printf("Current Cycle: %d\n", cpu->currentCycle);
		
		// loop over all processes
		for(int i = 0; i < MAX_PROCESSES; i++)
			// check process needs to be inserted in your respective IO queue 
			check_process_is_starting_io(cpu, cpu->processes[i]);
		
		// logical check to execute not finished processes
		execute_process(cpu);
		
		// execute io operation of waiting blocked processes
		execute_io_operation(cpu->ioDiskQueue);
		execute_io_operation(cpu->ioMagneticTapeQueue);
		execute_io_operation(cpu->ioPrinterQueue);
		
		// loop over all processes
		for(int i = 0; i < MAX_PROCESSES; i++)
			// check arrival time of new processes to insert them on high priority queue
			if(cpu->processes[i]->arrivalTime == cpu->currentCycle)
				insert_new_process_on_high_priority_queue(cpu, cpu->processes[i]);
		
		// get process back to priority queue if its io has finished
		manage_process_back_from_io(cpu, cpu->ioDiskQueue);
		manage_process_back_from_io(cpu, cpu->ioMagneticTapeQueue);
		manage_process_back_from_io(cpu, cpu->ioPrinterQueue);
         
		// sleeping for debug proposes
		sleep(1);
		
		// printing all queues
		print_all_queues(cpu);
		
		// increment cycle counter
		cpu->currentCycle++;
		printf("\n\n\n");
	}
	
	printf("Simulation finished\n");
}


void print_all_queues(cpu_t* cpu)
{
	printf("\n");
	
	printf("- High Priority Queue:\n");
	print_queue(cpu->highPriorityQueue);
	
	printf("- Low Priority Queue:\n");
	print_queue(cpu->lowPriorityQueue);
	
	printf("- Disk IO Queue:\n");
	print_queue(cpu->ioDiskQueue);
	
	printf("- Magnetic Tape IO Queue:\n");
	print_queue(cpu->ioMagneticTapeQueue);
	
	printf("- Printer IO Queue:\n");
	print_queue(cpu->ioPrinterQueue);
}

bool check_only_one_process_is_being_executed(cpu_t* cpu)
{
	return (cpu->lowPriorityQueue->length == 0 && cpu->highPriorityQueue->length == 1) || 
		   (cpu->lowPriorityQueue->length == 1 && cpu->highPriorityQueue->length == 0);
}

void execute_process(cpu_t* cpu)
{
	// checking process to be executed
	process_t* process = get_next_process_to_be_executed(cpu);
	if(process == NULL) return;
	
	// conditions for normal running
	if(	(process->status == READY || process->status == RUNNING) && // process is at allowed status to execute
		process->missingCyclesToFinish != 0 && // process still have cycles to run
		( process->quantumCounter < QUANTUM || check_only_one_process_is_being_executed(cpu) ) ) // quantum counter is lower than quantum or there is only one process to execute
	{
		process->status = RUNNING;
		process->missingCyclesToFinish--;
		process->quantumCounter++;
		printf("Process with PID %d is running now for cycle %d/%d\n", process->pid
																	 , process->burstTime - process->missingCyclesToFinish
																	 , process->burstTime);
	}
	
	// conditions to finalize process execution
	else if( process->missingCyclesToFinish == 0 && // no more cycles to execute
			 process->status != FINISHED && //  not handled status
			 process->io->status == FINISHED) // io operation is finished
	{
		process->status = FINISHED;
		printf("Process with PID %d finished\n", process->pid);
		
		// removing from queues
		remove_process_from_priority_queues(cpu, process);
		
		// reseting quantum
		process->quantumCounter = 0;
	}
	
	// handle process that needs to run but quantum has expired
	else if(process->quantumCounter >= QUANTUM && process->status == RUNNING)
	{
		process->status = READY;
		printf("Process with PID %d was blocked due to quantum and moved to low priority queue\n", process->pid);
		
		remove_process_from_priority_queues(cpu, process);
		
		// reset quantum
		process->quantumCounter = 0;
		
		// add process to low priority queue
		push(cpu->lowPriorityQueue, process);
		
		// execute next process on the same cycle previous process was blocked by quantum
		process_t* nextProcess = get_next_process_to_be_executed(cpu);
		if(nextProcess != NULL)
		{
			nextProcess->status = RUNNING;
			nextProcess->missingCyclesToFinish--;
			nextProcess->quantumCounter++;
			printf("Process with PID %d is running now for %d/%d cycles\n", nextProcess->pid
																		  , nextProcess->burstTime-nextProcess->missingCyclesToFinish
																	      , nextProcess->burstTime);
		}
			
	}
	
		
}


process_t* get_next_process_to_be_executed(cpu_t* cpu)
{
	// checking high priority queue
	if(cpu->highPriorityQueue->length > 0)
	{
		// getting element from first process at queue
		queue_element_t* e = front(cpu->highPriorityQueue);
		return e->process;
	}
	
	// checking low priority queue
	if(cpu->lowPriorityQueue->length > 0)
	{
		// getting element from first process at queue
		queue_element_t* e = front(cpu->lowPriorityQueue);
		return e->process;
	}
	
	// return NULL if there is no process to execute
	return NULL;
}


void manage_process_back_from_io(cpu_t* cpu, queue_t* queue)
{
	// checking first process from queue is valid
	if(queue->first == NULL) return;
	process_t* process = front(queue)->process;
	
	// checking IO operation has finished and not handled
	if(	process->io->usingTime == process->io->burstTime &&
		process->io->status != FINISHED)
	{
		process->status = READY;
		process->io->status = FINISHED;
		
		// move process from io queue to priority queue
		switch(process->io->type)
		{
			case DISK:
				pop(cpu->ioDiskQueue);
				push(cpu->lowPriorityQueue, process); // from disk io to low priority queue
				printf("Process with PID %d moved from disk io queue to low priority queue\n", process->pid);
				break;
	
			case MAGNETIC_TAPE:
				pop(cpu->ioMagneticTapeQueue);
				push(cpu->highPriorityQueue, process); // from magnetic tape io to high priority queue
				printf("Process with PID %d moved from magnetic tape io queue to high priority queue\n", process->pid);
				break;
			
			case PRINTER:
				pop(cpu->ioPrinterQueue);
				push(cpu->highPriorityQueue, process); // from printer io to high priority queue
				printf("Process with PID %d moved from printer io queue to high priority queue\n", process->pid);
				break;
				
			default: break;
			
		}
	}
}

void execute_io_operation(queue_t* queue)
{
	// executing io from first process at desired queue
	if(queue->first != NULL)			
	{
		process_t* process = front(queue)->process;
		process->io->usingTime++;
		process->io->status = RUNNING;
		
		printf("Process with PID %d had its %s IO operation executed for %d/%d cycles\n", process->pid
																						, get_string_from_io_type(process->io->type)
																						, process->io->usingTime
																						, process->io->burstTime);
	}
}

void insert_new_process_on_high_priority_queue(cpu_t* cpu, process_t* process)
{
	push(cpu->highPriorityQueue, process);
	printf("Process with PID %d was added to high priority queue for first time\n", process->pid);
	process->status = READY;
}

void check_process_is_starting_io(cpu_t* cpu, process_t* process)
{
	// check process is at time to start io operation
	if(	process->burstTime - process->missingCyclesToFinish == process->io->relativeStart &&
		process->io->status == NOT_STARTED)
	{
		
		remove_process_from_priority_queues(cpu, process);
		
		switch (process->io->type)
		{
			case DISK:
				process->status = BLOCKED;
				process->io->status = READY;
				push(cpu->ioDiskQueue, process);
				printf("Process with PID %d was blocked due to IO (added to disk queue)\n", process->pid);
				break;
			
			case MAGNETIC_TAPE:
				process->status = BLOCKED;
				process->io->status = READY;
				push(cpu->ioMagneticTapeQueue, process);
				printf("Process with PID %d was blocked due to IO (added to magnetic tape queue)\n", process->pid);
				break;
				
			case PRINTER:
				process->status = BLOCKED;
				process->io->status = READY;
				push(cpu->ioPrinterQueue, process);
				printf("Process with PID %d was blocked due to IO (added to printer queue)\n", process->pid);
				break;
			
			default:
				break;
		}	
	}
}


void remove_process_from_priority_queues(cpu_t* cpu, process_t* process)
{
	// remove if its exists in queue
	// same effect that the pop operation
	remove_process(cpu->highPriorityQueue, process);
	remove_process(cpu->lowPriorityQueue, process);
}





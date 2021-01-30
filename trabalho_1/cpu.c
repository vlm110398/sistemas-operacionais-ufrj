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
	
	while(all_process_has_finished(cpu->processes) == FALSE && cpu->currentCycle < MAX_CYCLES)
	{	
		printf("Current Cycle: %d\n", cpu->currentCycle);
		if(cpu->currentProcess != NULL && (cpu->currentProcess->status == READY || cpu->currentProcess->status == RUNNING) && cpu->currentProcess->missingCyclesToFinish != 0 && cpu->currentProcess->quantumCounter % QUANTUM != 0){
			cpu->currentProcess->missingCyclesToFinish--;
			cpu->currentProcess->quantumCounter++;
			printf("Process with PID %d is running now\n", cpu->currentProcess->pid);		
		}
		else{
			if(cpu->currentProcess != NULL){
				if(cpu->currentProcess->missingCyclesToFinish == 0 && cpu->currentProcess->status != FINISHED && cpu->currentProcess->alreadyOutIoQueue == TRUE){
					cpu->currentProcess->status = FINISHED;
					printf("Process with PID %d is finished\n", cpu->currentProcess->pid);
					remove_process(cpu->highPriorityQueue, cpu->currentProcess);
					remove_process(cpu->lowPriorityQueue, cpu->currentProcess);

				}
				else if(cpu->currentProcess->quantumCounter - QUANTUM == 0 && cpu->currentProcess->status == RUNNING){
					cpu->currentProcess->status = BLOCKED;
					cpu->currentProcess->quantumCounter = 0;
					printf("Process with PID %d is blocked by quantum.\n", cpu->currentProcess->pid);
					// remove if its exists in queue
					// same effect that the pop operation
					// because this process is the first of your respective queue
					remove_process(cpu->highPriorityQueue, cpu->currentProcess);
					remove_process(cpu->lowPriorityQueue, cpu->currentProcess);
					push(cpu->lowPriorityQueue, cpu->currentProcess);
				}
				
			}
			if(cpu->currentProcess == NULL || cpu->currentProcess->status == FINISHED || cpu->currentProcess->status == BLOCKED){
				process_t* nextProcess = get_next_process_to_be_executed(cpu);
				if(nextProcess != NULL){
					nextProcess->status = RUNNING;
					nextProcess->missingCyclesToFinish--;
					nextProcess->quantumCounter++;
					printf("Process with PID %d is running now for %d/%d cycles\n", nextProcess->pid, nextProcess->burstTime-nextProcess->missingCyclesToFinish, nextProcess->burstTime);
					cpu->currentProcess = nextProcess;
				}			
			}
		}
		

		// loop over all processes
		for(int i = 0; i < MAX_PROCESSES; i++){
			// check arrival time of new processes to insert them on high priority queue
			if(cpu->processes[i]->arrivalTime == cpu->currentCycle){
				push(cpu->highPriorityQueue, cpu->processes[i]);
				printf("Process with PID %d was added to high priority queue\n", cpu->processes[i]->pid);
				cpu->processes[i]->status = READY;
			}
			// when the process is inserted in your respective IO queue 
			if(cpu->processes[i]->burstTime - cpu->processes[i]->missingCyclesToFinish  == cpu->processes[i]->io->relativeStart && !cpu->processes[i]->alreadyInIoQueue){
				switch (cpu->processes[i]->io->type)
				{
					case DISK:
						push(cpu->ioDiskQueue, cpu->processes[i]);
						cpu->processes[i]->alreadyInIoQueue = TRUE;
						printf("Process with PID %d was added to DISK queue\n", cpu->processes[i]->pid);
						break;
					case MAGNETIC_TAPE:
						push(cpu->ioMagneticTapeQueue, cpu->processes[i]);
						cpu->processes[i]->alreadyInIoQueue = TRUE;
						printf("Process with PID %d was added to MAGNETIC TAPE queue\n", cpu->processes[i]->pid);
						break;
					case PRINTER:
						push(cpu->ioPrinterQueue, cpu->processes[i]);
						cpu->processes[i]->alreadyInIoQueue = TRUE;
						printf("Process with PID %d was added to PRINTER queue\n", cpu->processes[i]->pid);
						break;
					default:
						break;
				}	
			}
			if(cpu->ioDiskQueue->first != NULL && cpu->processes[i] == cpu->ioDiskQueue->first->process){
				cpu->processes[i]->status = BLOCKED; 
				cpu->processes[i]->quantumCounter = 0;
				++cpu->processes[i]->io->usingTime;		
				printf("Process with PID %d was blocked because:\n", cpu->processes[i]->pid);
				printf("is using DISK for %d/%d cycles.\n", cpu->processes[i]->io->usingTime, cpu->processes[i]->io->burstTime);
			}
			else if(cpu->ioMagneticTapeQueue->first != NULL && cpu->processes[i] == cpu->ioMagneticTapeQueue->first->process){
				cpu->processes[i]->status = BLOCKED;
				++cpu->processes[i]->io->usingTime;
				cpu->processes[i]->quantumCounter = 0;
				printf("Process with PID %d was blocked because:\n", cpu->processes[i]->pid);
				printf("is using MAGNETIC TAPE for %d/%d cycles.\n", cpu->processes[i]->io->usingTime, cpu->processes[i]->io->burstTime);
				
			}
			else if(cpu->ioPrinterQueue->first != NULL && cpu->processes[i] == cpu->ioPrinterQueue->first->process){
				cpu->processes[i]->status = BLOCKED;
				++cpu->processes[i]->io->usingTime;
				cpu->processes[i]->quantumCounter = 0;
				printf("Process with PID %d was blocked because:\n", cpu->processes[i]->pid);
				printf("is using PRINTER for %d/%d cycles.\n", cpu->processes[i]->io->usingTime, cpu->processes[i]->io->burstTime);
			}
			// remove from IO queue
			if(cpu->processes[i]->io->usingTime == cpu->processes[i]->io->burstTime && !cpu->processes[i]->alreadyOutIoQueue){
				cpu->processes[i]->status = RUNNING;
				cpu->processes[i]->alreadyOutIoQueue = TRUE;
				switch(cpu->processes[i]->io->type){
					case DISK:
					pop(cpu->ioDiskQueue);
					push(cpu->lowPriorityQueue,cpu->processes[i]);
					break;

					case MAGNETIC_TAPE:
					pop(cpu->ioMagneticTapeQueue);
					push(cpu->highPriorityQueue,cpu->processes[i]);
					break;
					
					case PRINTER:
					pop(cpu->ioPrinterQueue);
					push(cpu->highPriorityQueue,cpu->processes[i]);
					break;
					default:
					break;
				}
			}				


			


		
		}	


         
		// sleeping for debug proposes
//		sleep(1);
		
		// increment cycle counter
		cpu->currentCycle++;
		printf("\n");
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



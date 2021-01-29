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
		// loop over all processes
		for(int i = 0; i < MAX_PROCESSES; i++){
			
			// check arrival time of new processes to insert them on high priority queue
			if(cpu->processes[i]->arrivalTime == cpu->currentCycle){
				push(cpu->highPriorityQueue, cpu->processes[i]);
				printf("Process with PID %d was added to high priority queue\n", cpu->processes[i]->pid);
				cpu->processes[i]->status = READY;
			}	
			
			// when the process is inserted in your respective IO queue 
			if(cpu->processes[i]->arrivalTime + cpu->processes[i]->io->relativeStart == cpu->currentCycle ){
				switch (cpu->processes[i]->io->type)
				{
					case DISK:
						push(cpu->ioDiskQueue, cpu->processes[i]);
						printf("Process with PID %d was added to DISK queue\n", cpu->processes[i]->pid);
						break;
					case MAGNETIC_TAPE:
						push(cpu->ioMagneticTapeQueue, cpu->processes[i]);
						printf("Process with PID %d was added to MAGNETIC TAPE queue\n", cpu->processes[i]->pid);
						break;
					case PRINTER:
						push(cpu->ioPrinterQueue, cpu->processes[i]);
						printf("Process with PID %d was added to PRINTER queue\n", cpu->processes[i]->pid);
						break;
					default:
						break;
				}
				

			}
/*			
			// remove from IO queue
			if(cpu->processes[i]->io->usingTime == cpu->processes[i]->io->burstTime){
				cpu->processes[i]->status = RUNNING;
				switch(cpu->processes[i]->io->type){
					case DISK:
					pop(cpu->ioDiskQueue);
					break;

					case MAGNETIC_TAPE:
					pop(cpu->ioMagneticTapeQueue);
					break;
					
					case PRINTER:
					pop(cpu->ioPrinterQueue);
					break;

					default:
					break;
				}
			}
*/
		}
		//another check loop because an I / O queue may have had a process removed 
		//after passing the loop to another new process in the queue
		for(int i = 0; i < MAX_PROCESSES; i++){
			if(cpu->ioDiskQueue->first != NULL && cpu->processes[i] == cpu->ioDiskQueue->first->process){
				cpu->processes[i]->status = BLOCKED; 
				++cpu->processes[i]->io->usingTime;
				printf("Process with PID %d is using DISK for %d cycles.\n", cpu->processes[i]->pid, cpu->processes[i]->io->usingTime);
				
			}
			else if(cpu->ioMagneticTapeQueue->first != NULL && cpu->processes[i] == cpu->ioMagneticTapeQueue->first->process){
				cpu->processes[i]->status = BLOCKED;
				++cpu->processes[i]->io->usingTime;
				printf("Process with PID %d is using MAGNETIC TAPE for %d cycles.\n", cpu->processes[i]->pid, cpu->processes[i]->io->usingTime);
				
			}
			else if(cpu->ioPrinterQueue->first != NULL && cpu->processes[i] == cpu->ioPrinterQueue->first->process){
				cpu->processes[i]->status = BLOCKED;
				++cpu->processes[i]->io->usingTime;
				printf("Process with PID %d is using PRINTER for %d cycles.\n", cpu->processes[i]->pid, cpu->processes[i]->io->usingTime);
			}
		}

		if(cpu->currentProcess != NULL  && cpu->currentProcess->missingCyclesToFinish != 0 && cpu->currentProcess->quantumCounter % QUANTUM != 0){
			cpu->currentProcess->missingCyclesToFinish--;
			cpu->currentProcess->quantumCounter++;
			printf("Process with PID %d is running now\n", cpu->currentProcess->pid);									
		}
		
		else{
			if(cpu->currentProcess != NULL){
				if(cpu->currentProcess->missingCyclesToFinish == 0){
					cpu->currentProcess->status = FINISHED;
					/*
					if(cpu->highPriorityQueue->first->process == cpu->currentProcess){
						pop(cpu->highPriorityQueue);
					}
					else if(cpu->lowPriorityQueue->first->process == cpu->currentProcess){
						pop(cpu->lowPriorityQueue);
					}
					*/
					printf("Process with PID %d is finished\n", cpu->currentProcess->pid);
				}
				else{
					cpu->currentProcess->status = BLOCKED;
					printf("Process with PID %d is blocked\n", cpu->currentProcess->pid);
					if(cpu->currentProcess->quantumCounter % QUANTUM == 0){
						push(cpu->lowPriorityQueue, cpu->currentProcess);
					}

				}
			} 
			// check if is there any process to be executed
			process_t* nextProcess = get_next_process_to_be_executed(cpu);
			if(nextProcess != NULL){
				nextProcess->status = RUNNING;
				nextProcess->missingCyclesToFinish--;
				nextProcess->quantumCounter++;
				printf("Process with PID %d is running now\n", nextProcess->pid);
				cpu->currentProcess = nextProcess;
			}
		}

		         
		// sleeping for debug proposes
		sleep(1);
		
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



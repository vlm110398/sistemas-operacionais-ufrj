#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
#include "process.h"
#include "io.h"
#include "queue.h"

typedef struct {
	
	int currentCycle;
	
	process_t** processes;
	
	queue_t* lowPriorityQueue;
	queue_t* highPriorityQueue;
	
	queue_t* ioDiskQueue;
	queue_t* ioPrinterQueue;
	queue_t* ioMagneticTapeQueue;
	
} cpu_t;

// initializes cpu struct
cpu_t* init_cpu(process_t** processes);

// check all processes are at finished status
bool all_process_has_finished(process_t** processes);

// initialize simulation loop
void start_simulation(cpu_t* cpu);

// return next process to be executed
process_t* get_next_process_to_be_executed(cpu_t* cpu);

// print priority and io queues
void print_all_queues(cpu_t* cpu);

// remove process from both priority queues
void remove_process_from_priority_queues(cpu_t* cpu, process_t* process);

// manage current process execution and preemption
void execute_process(cpu_t* cpu);

// insert process backing from IO on priority queue according to IO type
void manage_process_back_from_io(cpu_t* cpu, queue_t* queue);

// insert new process to high priority queue at corresponding arrival time
void insert_new_process_on_high_priority_queue(cpu_t* cpu, process_t* process);

// execute io of process from desired io queue
void execute_io_operation(queue_t* queue);

// check process io is at relative start from process execution
void check_process_is_starting_io(cpu_t* cpu, process_t* process);

// checks if only one process (from both queues) is executing at the time
bool check_only_one_process_is_being_executed(cpu_t* cpu);

#endif

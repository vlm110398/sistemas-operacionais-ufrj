#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "process.h"
#include "io.h"

typedef struct queue_element_t
{ 	
	process_t* process;				// current element process
	struct queue_element_t* next; 	// next element pointer

} queue_element_t;


typedef struct
{
    QUEUE_TYPE type;		// queue type
    queue_element_t* first;	// first element from queue
	int length;				// queue size
} queue_t;


// initializes queue data structure
queue_t * init_queue(QUEUE_TYPE queueType);

// push element to the end of desired queue
void push(queue_t* q, process_t* process);

// pop and return first element from queue
queue_element_t* pop(queue_t* q);

// print desired queue content
void print_queue(queue_t* q);

// initialize queue element with desired process
queue_element_t* init_queue_element(process_t* process);

// return first element from queue without removing it
queue_element_t* front(queue_t* q);

// remove desired process from desired queue
void remove_process(queue_t * q, process_t * p);


#endif

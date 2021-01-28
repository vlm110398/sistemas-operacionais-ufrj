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
	int beginTime;					// starting time
	int endTime;  					// finishing time
	int tempBeginTime;				// auxiliar starting time variable
	int tempEndTime;				// auxiliar finishing time variable
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
void push(queue_t* q, process_t* element);

// pop and return first element from queue
queue_element_t* pop(queue_t* q);

// print desired queue content
void print_queue(queue_t* q);



#endif

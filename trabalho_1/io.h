#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include "constants.h"

typedef struct
{
    int startTime;			 // start time
	int finishTime;			 // finish time
    int burstTime;      	 // burst time
    int relativeStart;  	 // time of start relative from process start
    int usingTime; 			 // current cycle of io execution
    IO_TYPE type;			 // IO type
	EXECUTION_STATUS status; // IO current status
	
} io_t;

// initialize io
io_t* init_io(IO_TYPE ioType);

// initialize random io operation
io_t* init_random_io();

// get string representation of io type
char* get_string_from_io_type(IO_TYPE ioType);

#endif

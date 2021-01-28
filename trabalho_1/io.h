#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include "constants.h"

typedef struct{
    int startTime;	// start time
	int finishTime;	// finish time
    IO_TYPE type;	// IO type
} io_t;

// initialize io
io_t* init_io(IO_TYPE ioType);

// initialize random io operation
io_t* init_random_io();

#endif

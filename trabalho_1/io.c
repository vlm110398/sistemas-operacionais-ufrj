#include "io.h"

#include <stdlib.h>

io_t* init_io()
{
	io_t* io = (io_t*) malloc(sizeof(io_t));
	
	return io;
}
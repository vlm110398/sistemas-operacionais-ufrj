#include "io.h"



io_t* init_io(IO_TYPE ioType)
{
	io_t* io = (io_t*) malloc(sizeof(io_t));
	
	io->type = ioType;
	io->startTime = 0;
	io->finishTime = 0;
	
	return io;
}

io_t* init_random_io()
{
	io_t* io = (io_t*) malloc(sizeof(io_t));
	
	io->type = rand() % IO_TYPE_NUMBER;
	io->startTime = 0;
	io->finishTime = 0;
	
	return io;
}
#include "io.h"



io_t* init_io(IO_TYPE ioType)
{
	io_t* io = (io_t*) malloc(sizeof(io_t));
	
	io->type = ioType;
	io->startTime = 0;
	io->finishTime = 0;
	io->burstTime = (rand() % MAX_IO_BURST_TIME) + 1; // certify burst time is not zero
	io->usingTime = 0;
	io->relativeStart = 0;
	io->status = NOT_STARTED;

	return io;
}

io_t* init_random_io()
{
	io_t* io = (io_t*) malloc(sizeof(io_t));
	
	io->type = rand() % IO_TYPE_NUMBER;
	io->startTime = 0;
	io->finishTime = 0;
	io->burstTime = (rand() % MAX_IO_BURST_TIME) + 1; // certify burst time is not zero
	io->usingTime = 0;
	io->status = NOT_STARTED;
	// io relativeStart will be defined at process creation because this value must be minor than process burst time
	
	return io;
}

char* get_string_from_io_type(IO_TYPE ioType)
{
	switch(ioType)
	{
		case DISK:
			return "Disk";
		case MAGNETIC_TAPE: 
			return "Magnetic Tape";
		case PRINTER:
			return "Printer";
		default:
			return "None";
	}
}
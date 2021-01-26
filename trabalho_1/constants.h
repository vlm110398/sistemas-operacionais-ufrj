#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum  { 
    NOT_STARTED, READY, BLOCKED, RUNNING, FINISHED 
} PROCESS_STATUS;

typedef enum {
    DISK, MAGNETIC_TAPE, PRINTER
} IO_TYPE;

typedef enum  { 
  IO_QUEUE, PROCESS_QUEUE, READY_QUEUE, GANTT_QUEUE 
} QUEUE_TYPE;

// only used in ready queue
typedef enum  { 
  IO, PROCESS
} ELEM_TYPE;


#endif /* CONSTANTS_H */
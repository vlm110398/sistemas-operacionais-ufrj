#ifndef PROCESS_H
#define PRCESS_H
#include "constants.h"


typedef struct{
    int  pid;
    int ppid;
    PROCESS_STATUS status;
    int arrivalTime;
    int burstTime;
} process;

process * initProcess();

#endif /* PROCESS_H */

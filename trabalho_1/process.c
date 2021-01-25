#include "process.h"
#include <stdlib.h>
process * initProcess(int pid){
    process * proc = (process *) malloc(sizeof(process));
    proc -> pid = pid;
    return proc;
}
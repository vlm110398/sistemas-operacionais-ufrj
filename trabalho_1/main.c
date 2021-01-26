#include<stdio.h>

#include "constants.h"
#include "queue.h"

int main(){

    queue_t * q  = init_queue(LOW_PRIORITY_QUEUE);
 
    process_t * proc1 = init_process(0, 0, NULL);
    process_t * proc2 = init_process(1, 1, proc1);

    push(q, (void*)proc1, PROCESS_ELEMENT);
    push(q, (void*)proc2, PROCESS_ELEMENT);
    pop(q);
    pop(q);

    return 0;
}
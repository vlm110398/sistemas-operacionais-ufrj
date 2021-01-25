#include<stdio.h>
#include"queue.h" 
int main(){

    queue * q  = initQueue(1,1, PROCESS);
    process * proc1 = initProcess(1);
    process * proc2 = initProcess(2);

    enqueueProcess(q, proc1); 
    enqueueProcess(q, proc2);
    dequeueIo(q);
    dequeueProcess(q);
    dequeueProcess(q);
    dequeueProcess(q);
    printf("");

    return 0;
}
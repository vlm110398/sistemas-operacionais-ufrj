#include "queue.h"
#include "stdio.h"
#include "stdlib.h"

queue * initQueue(int priority, int quantum, queueType qType){
    queue * q = (queue *) malloc(sizeof(queue));
    q->priority = priority;
    q->quantum = quantum;
    q->first = NULL;
    q->type = qType;

    return q;
}
void enqueueIo(queue * q,io * i_o){
    if(q->type == PROCESS){
        printf("Essa fila é exclusiva de IO\n");
    }
    element * elem = (element *) malloc(sizeof(element));
    elem->i_o = i_o;
    elem->next = NULL;
    enqueueElement(q,elem);
}
void enqueueProcess(queue *q,process * proc){
    if(q->type == IO){
        printf("Essa fila é exclusiva de processos\n");
    }
    element * elem = (element *) malloc(sizeof(element));
    elem->proc = proc;
    elem->next = NULL;
    enqueueElement(q,elem);
}


void enqueueElement (queue * q, element * elem){

    if(q->first != NULL){
        element * nextElem = q->first;
        while(nextElem->next != NULL){
            nextElem = nextElem->next; 
        }
        nextElem->next = elem;
    }
    else{
         
        q->first = elem;
    } 
}
io * dequeueIo(queue *q){
    if(q->type == PROCESS){
        printf("This queue is IO exclusive\n");
        return NULL;
    }
    element * elem = dequeueElement(q);
    if(elem == NULL){
        return NULL;
    }
    io * i_o = elem->i_o;
    free(elem);
    return i_o; 
}
process * dequeueProcess(queue *q){
    if(q->type == IO){
        printf("This queue is process exclusive\n");
    }    
    element * elem = dequeueElement(q);
    if(elem == NULL){
        return NULL;
    }
    process * proc = elem->proc;
    free(elem);
    return proc; 
    
}
element * dequeueElement (queue * q){
    if(q->first == NULL){
        printf("This queue is empty\n");
        return NULL;
    }
    else{
        element * oldFirst = q->first; 
        if(q->first->next != NULL){
            element * newFirst = q->first->next;
            q->first = newFirst;
        }
        else{
            q->first = NULL;    
        }       
        return oldFirst;     
    }    
}
void printQueue(queue *q){

}

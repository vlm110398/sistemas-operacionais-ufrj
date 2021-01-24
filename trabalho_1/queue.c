#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
queue * init(int priority, int quantum){
    queue * q;
    q->priority = priority;
    q->quantum = quantum;
    return q;
}
void push (queue * q, element * elem){
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
element  pop (queue * q){
    if(q->first == NULL)
        printf("Fila ja esta vazia");
    else{
        if(q->first->next != NULL){
            element * newFirst = q->first->next;
            element oldFirst = *(q->first); 
            free(q->first);
            q->first = newFirst;
            return oldFirst;
        }
        else{
            element oldFirst = *(q->first);
            free(q->first);         
            return oldFirst;
        }            
    }    
}
void printQueue(queue *q){
}

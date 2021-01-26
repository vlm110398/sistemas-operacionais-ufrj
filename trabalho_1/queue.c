#include "queue.h"

queue_t * init_queue(QUEUE_TYPE queueType)
{
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    q->first = NULL;
    q->type = queueType;
    return q;
}

void push(queue_t* q, void* element, ELEMENT_TYPE elementType)
{
	// creating queue element
	queue_element_t* e = (queue_element_t*) malloc(sizeof(queue_element_t));
    e->next = NULL;
	if(elementType == PROCESS_ELEMENT) e->process = (process_t*) element;
	else if(elementType == IO_ELEMENT) e->io = (io_t*) element;
    
	// inserting on the queue
    if(q->first != NULL){
        queue_element_t* crrtElement = q->first;
        while(crrtElement->next != NULL) crrtElement = crrtElement->next; 
        crrtElement->next = e;
    }
    else 
		q->first = e;
}


queue_element_t* pop(queue_t* q)
{
    if(q->first == NULL){
        printf("This queue is empty\n");
        return NULL;
    }
    else{
        queue_element_t* first = q->first; 
        if(first->next != NULL){
            queue_element_t* newFirst = first->next;
            q->first = newFirst;
        }
        else q->first = NULL;
		
		return first;     
    } 
}


void print_queue(queue_t* q)
{

}

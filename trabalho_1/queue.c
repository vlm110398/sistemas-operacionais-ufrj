#include "queue.h"

queue_t * init_queue(QUEUE_TYPE queueType)
{
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    q->first = NULL;
    q->type = queueType;
	q->length = 0;
    return q;
}

queue_element_t* init_queue_element(process_t* process)
{
	queue_element_t* e = (queue_element_t*) malloc(sizeof(queue_element_t));
	e->next = NULL;
	e->process = process;
	e->beginTime = 0;
	e->endTime = 0;
	e->tempBeginTime = 0;
	e->tempEndTime = 0;
	return e;
}

void push(queue_t* q, process_t* process)
{
	// creating queue element
	queue_element_t* e = init_queue_element(process);
    
	// inserting on the queue
    if(q->first != NULL){
        queue_element_t* crrtElement = q->first;
        while(crrtElement->next != NULL) crrtElement = crrtElement->next; 
        crrtElement->next = e;
    }
    else 
		q->first = e;
	
	// increments queue size
	q->length++;
}


queue_element_t* pop(queue_t* q)
{
	// checking queue is empty
    if(q->first == NULL){
        printf("This queue is empty\n");
        return NULL;
    }
	// updating queue
    else{
        queue_element_t* first = q->first; 
        if(first->next != NULL){
            queue_element_t* newFirst = first->next;
            q->first = newFirst;
        }
        else q->first = NULL;
		
		// decrements queue size
		q->length--;
		
		return first;     
    }
}


void print_queue(queue_t* q)
{
	queue_element_t* crrtElement = q->first;
	
	for(int i = 0; i < q->length; i++)
	{
		print_process(crrtElement->process);
		printf("BeginTime:%d\tEndTime:%d\n", crrtElement->beginTime, crrtElement->endTime);
		crrtElement = crrtElement->next;
	}
}


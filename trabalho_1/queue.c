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
	return e;
}

void push(queue_t* q, process_t* process)
{
	// creating queue element
	queue_element_t* e = init_queue_element(process);
    
	// inserting on the end of the queue
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

queue_element_t* front(queue_t* q)
{
	// checking queue is empty
    if(q->first == NULL){
        //printf("This queue is empty\n");
        return NULL;
    }
    else return q->first; 
}


void remove_process(queue_t* q, process_t* p)
{
    if(q->first != NULL){
        if(q->first->process == p){
            pop(q);
        }
        else{
            queue_element_t * tmpBefore = q->first;
            while(tmpBefore->next != NULL){
                if(tmpBefore->next->process == p ){
                    queue_element_t * tmpCurr = tmpBefore->next;
                    --q->length;
                    if(tmpBefore->next->next == NULL){
                        tmpBefore->next = NULL;
                        free(tmpCurr);
                    }
                    else{
                        tmpBefore->next = tmpBefore->next->next;
                        free(tmpCurr);
                    }
                    break;
                }
                tmpBefore = tmpBefore->next;
            }
        }
    }
}

void print_queue(queue_t* q)
{
	queue_element_t* crrtElement = q->first;
	
	for(int i = 0; i < q->length; i++)
	{
		print_process(crrtElement->process);
		crrtElement = crrtElement->next;
	}
}


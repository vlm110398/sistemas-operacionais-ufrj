#ifndef QUEUE_H
#define QUEUE_H

#include "constants.h"
#include "process.h"
#include "io.h"


typedef struct element{
  // in process/io queue I know the type of enqueue element 
  // but in ready queue isn't
    union {
      process * proc;
      io * i_o;
    };

  // only used in ready/gantt queue type for round robin algorithm 
  int currentBeginTime;
  int currentEndTime;
  ELEM_TYPE type;
  struct element *next;

} element;
typedef struct queue{
    int priority;
    int quantum;  
    QUEUE_TYPE type;
    element * first;

} queue;

queue * initQueue(int priority, int quantum, QUEUE_TYPE qType);
void enqueueIo(queue * q,io * i_o);
void enqueueProcess(queue *q,process * proc);
void enqueueElement (queue * q, element * elem);

io * dequeueIo(queue *q);
process * dequeueProcess(queue *q);
element * dequeueElement (queue * q);

void printQueue(queue *q);



#endif /* QUEUE_H */
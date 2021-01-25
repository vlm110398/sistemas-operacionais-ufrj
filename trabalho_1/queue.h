#include "process.h"
#include "io.h" 
typedef enum queueType { 
  IO, PROCESS
} queueType;

typedef struct element{
    union {
      process * proc;
      io * i_o;
    };
  struct element *next;

} element;
typedef struct{
    int priority;
    int quantum;
    queueType type;
    element * first;

} queue;

queue * initQueue(int priority, int quantum, queueType qType);
void enqueueIo(queue * q,io * i_o);
void enqueueProcess(queue *q,process * proc);
void enqueueElement (queue * q, element * elem);

io * dequeueIo(queue *q);
process * dequeueProcess(queue *q);
element * dequeueElement (queue * q);

void printQueue(queue *q);
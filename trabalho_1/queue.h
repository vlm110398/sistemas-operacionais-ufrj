#include "process.h"
#include "io.h" 

typedef struct element{
    union {
      process * proc;
      io * io;
    };
  struct element *next;

} element;
typedef struct{
    int priority;
    int quantum;

    element * first;

} queue;


queue * init(int , int );
void push (queue * , element * );
element  pop (queue *);
void printQueue(queue *);
#include "process.h"
#include "io.h" 
typedef struct{
    union {
      process * proc;
      io * io;
    };
  element *next;

} element;
typedef struct{
    int priority;
    int quantum;

    element * first;

} queue;


queue * init(int priority);
void push (queue *, void *);
element * pop (queue *);

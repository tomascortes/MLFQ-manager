#pragma once
#ifndef __SIMPLE_QUEUE__
#define __SIMPLE_QUEUE__
#include "../process/process.h"

struct Queue;

extern struct Queue*
newQueue();

extern int
enqueue(struct Queue *q, Process *process);

extern void*
dequeue(struct Queue *q);

extern void
freeQueue(struct Queue *q);

extern int readyProcesses(struct Queue *q);

#endif
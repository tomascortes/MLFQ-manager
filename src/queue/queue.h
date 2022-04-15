#ifndef __SIMPLE_QUEUE__
#define __SIMPLE_QUEUE__
#include "../process/process.h"

static struct Node {
	Process *process;
	struct Node *next;
};
struct Queue {
	int size;
	int running;
	struct Node *head;
	struct Node *tail;
};
extern struct Queue* newQueue();

int enqueue(struct Queue *q, Process *process);

Process* dequeue(struct Queue *q);

extern void
freeQueue(struct Queue *q);

extern int readyProcesses(struct Queue *q);

void printQueue(struct Queue *q);

Process* startProcess(struct Queue *q, int cycle_num);
void actualizeRunning(struct Queue *q_now, struct Queue *q_next,struct Queue *finished, int quantum);
void actualizeCycle(struct Queue *q);
void actualizeWaits(struct Queue *q);
#endif
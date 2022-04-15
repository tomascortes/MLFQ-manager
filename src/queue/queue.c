#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
//codigo obtenido en https://gist.github.com/rdleon/d569a219c6144c4dfc04366fd6298554



struct Queue* newQueue()
{
	struct Queue *q;
	q = malloc(sizeof(struct Queue));

	if (q == NULL) {
		return q;
	}

	q->size = 0;
	q->running = 0;
	q->head = NULL;
	q->tail = NULL;

	return q;
}

int enqueue(struct Queue *q, Process *process)
{
	struct Node *node = malloc(sizeof(struct Node));
	if (node == NULL) {
		return q->size;
	}

	node->process = process;
	node->next = NULL;
	if (q->head == NULL) {
		q->head = node;
		q->tail = node;
		q->size = 1;

		return q->size;
	}


	q->tail->next = node;
	q->tail = node;
	q->size += 1;

	return q->size;
}

Process* dequeue(struct Queue *q)
{
	if (q->size == 0) {
		return NULL;
	}

	Process *process;
	struct Node *tmp = NULL;
	process = q->head->process;
	tmp = q->head;
	q->head = q->head->next;
	q->size -= 1;
	tmp -> process = NULL;
	free(tmp);

	return process;
}

int readyProcesses(struct Queue *q, int cycle)
{
	//retorna 1 si existe un proceso ready en la cola
	if (q == NULL) {
		return 0;
	}

	struct Node *tmp = q->head;
	while (tmp != NULL) {
        if (tmp->process->status == RUNNING) {
         // process2 = &tmp->process;
		 	q->running = 1;
			return 1;
		}
		tmp = tmp->next;
	}
	tmp = q->head;
	while (tmp != NULL){
		if (tmp->process->status == READY) {
         	tmp->process->status = RUNNING;
			q->running = 1;
			tmp->process->cpu_times += 1;
			if (tmp->process->response_time == 0){
				tmp->process->response_time += cycle;
				tmp->process->response_time -= tmp->process->start_cycle;
			}
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

void actualizeCycle(struct Queue *q)
{
	if (q == NULL) {
		return;
	}
	struct Node *tmp = q->head;
	while (tmp != NULL) {
		if (tmp->process-> status == READY) {
			tmp->process->waiting_time += 1;
		}
		else if (tmp->process-> status == WAITING) {
			tmp->process->waiting_time += 1;
			tmp->process->used_delay += 1;
		}
		else if (tmp->process-> status == RUNNING) {
			tmp->process->used_cycles += 1;
			tmp->process->used_waits += 1;
			tmp->process->quantum += 1;
		}
      tmp = tmp->next;
	}

	return;
}

void actualizeRunning(struct Queue *q_now, struct Queue *q_next,struct Queue *finished, int quantum, int cycle){
	if (q_now->head == NULL){
		return;
	}
	struct Node* node = q_now->head;
	struct Node* prev_node = NULL;
	int size =  q_now->size;
	for (int i =0;i < size; i++) {

		if (node->process->status == RUNNING){
			// ver si termino
			if (node->process->used_cycles >= node->process->cycles) {
				node->process->status = FINISHED;
				node->process->turnaround_time = cycle - node->process->start_cycle;
				enqueue(finished, node->process);
				q_now->running = 0;
				// sacar proceso
				if (prev_node!= NULL){
					prev_node->next = node->next;
					q_now ->size -= 1;
				}
				else{
					q_now->head = node->next;
					q_now->size -=1;
				}
				free(node);

			}
			//ver si le toca wait
			else if (node->process->used_waits >= node->process->wait){
				node->process->status = WAITING;
				q_now->running = 0;
				node->process->used_waits = 0;
			}

			// ver si termino su quantum
			else if (node->process->quantum >= quantum ){
				node->process->status = READY;
				node->process->interrupted_times += 1;
				q_now->running = 0;
				node->process->quantum = 0;
				if(prev_node == NULL){
					enqueue(q_next, dequeue(q_now));
				}
				else{
					prev_node->next = node->next;
					q_now->size -= 1;
					if (node->next == NULL){
						q_now -> tail = prev_node;
					}
					enqueue(q_next, node->process);
					free(node);
				}
			}
			return;
		}
		prev_node = node;
		node = node ->next;
	}
	return;
}


void actualizeWaits(struct Queue *q)
{
	// pasar los waits cumplidos a READY
	if (q == NULL) {
		return;
	}
	struct Node *tmp = q->head;
	while (tmp != NULL) {
		if (tmp->process-> status == WAITING) {
			if (tmp->process->used_delay == tmp->process->wait_delay){
				tmp->process->status = READY;
				tmp->process->used_waits = 0;
			}
		}

      tmp = tmp->next;
	}

	return;
}


Process* startProcess(struct Queue *q, int cycle_num){
	if (q->head == NULL){
		return NULL;
	}
	Process *pro;
	for (int i =0;i < q->size; i++) {
		pro = dequeue(q);
		if (pro->start_cycle == cycle_num){
			return pro;
		}
		else{
			enqueue(q, pro);
		}
	}
	return NULL;
}


void actualizeS(struct Queue *queue_a, struct Queue *queue_now)
{
	//retorna 1 si existe un proceso ready en la cola
	if (queue_now->head == NULL) {
		return;
	}
	struct Node *node = queue_now->head;
	struct Node *prev_node = NULL;

	while (node != NULL) {
		if (node->process-> status == READY || node->process-> status == WAITING) {
			node->process->used_s += 1;
			if  (node->process-> used_s >= node->process->s){
				if (prev_node == NULL){
					node->process->used_s = 0;
					enqueue(queue_a, dequeue(queue_now));
					node = queue_now->head;
				}
				else{
					prev_node->next = node->next;
					queue_now ->size -= 1;
					if (node->next == NULL){
						queue_now -> tail = prev_node;
					}
					node->process->used_s = 0;
					enqueue(queue_a, node->process);
					free(node);
					node = prev_node->next;
				}
			}
		}
		if (node == NULL){
			return;
		}
		prev_node = node;
		node = node->next;//acaa
	}
	return;
}

void freeQueue(struct Queue *q)
{
	if (q == NULL) {
		free(q);
		return;
	}
	Process *tmp = dequeue(q);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = dequeue(q);
	}
	free(q);
}



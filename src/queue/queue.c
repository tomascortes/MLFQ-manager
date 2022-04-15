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

int readyProcesses(struct Queue *q)
{
	//retorna 1 si existe un proceso ready en la cola
	if (q == NULL) {
		return 0;
	}
   
	struct Node *tmp = q->head;
	while (tmp != NULL) {
        if (tmp->process->status == 3) {
         // process2 = &tmp->process;
			return 1;
		}
		tmp = tmp->next;
	}
	tmp = q->head;
	while (tmp != NULL){
		if (tmp->process->status == 0) {
         	// process2 = &tmp->process;
         	tmp->process->status = 3;
         	printf("Proceso %d cambia a status %d\n", tmp->process->pid, tmp->process->status);
			return 1;
		}
		tmp = tmp->next;
	}
	return 1;
}

void actualizeCycle(struct Queue *q)
{
	//retorna 1 si existe un proceso ready en la cola
	if (q == NULL) {
		return;
	}
	struct Node *tmp = q->head;
	while (tmp != NULL) {
		if (tmp->process-> status == READY) {
			tmp->process->waiting_time += 1;
         	printf("Proceso %d tiene waiting_time de %d ciclos \n", tmp->process->pid, tmp->process->waiting_time);
		}
		else if (tmp->process-> status == WAITING) {
			tmp->process->waiting_time += 1;
			tmp->process->used_delay += 1;
			printf("Proceso %d tiene waiting_time de %d ciclos \n", tmp->process->pid, tmp->process->waiting_time);
			if (tmp->process->used_delay >= tmp->process->wait_delay){
				printf("Proceso %d entra en estado READY \n", tmp->process->pid);
				tmp->process->status = 0;
				tmp->process->used_waits = 0;
			}
		}
		else if (tmp->process-> status == RUNNING) {
			if (tmp->process->used_waits < tmp->process->wait){
				tmp->process->used_cycles += 1;
				tmp->process->used_waits += 1;
				printf("Proceso %d avanzo en %d ciclos \n", tmp->process->pid, tmp->process->used_cycles);
			}
			else if (tmp->process->used_cycles < tmp->process->cycles) {
				printf("Proceso %d entra en wait tras %d ciclos \n", tmp->process->pid, tmp->process->used_waits);
				tmp->process->status = 1;
				tmp->process->waiting_time += 1;
				tmp->process->used_delay += 1;
			}
			else {
				printf("Proceso %d termina tras %d ciclos \n", tmp->process->pid, tmp->process->used_cycles);
				tmp->process->status = 2;
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

void printQueue(struct Queue *q){
	if (q->head == NULL){
		printf("[]");
		return;
	}
	printf("[");
	struct Node *tmp = q->head;
	for (int i =0;i < q->size; i++) {
		printf("name: %s, ",tmp->process->name);
		printf("pid: %d, ",tmp->process->pid);
		tmp = tmp->next;
	}
	return;
}
// void actualizeS(struct Queue *q)
// {
// 	//retorna 1 si existe un proceso ready en la cola
// 	if (q == NULL) {
// 		return;
// 	}
// 	struct Queue *temp = q;

// 	while (q->head != NULL) {
// 		struct Node *tmp = q->head;
// 		if (tmp->process-> status == READY) {
// 			tmp->process->s += 1;
// 		}
// 		else if (tmp->process-> status == WAITING) {
// 			tmp->process->s += 1;
// 		}
// 	}
// 	return;
// }

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



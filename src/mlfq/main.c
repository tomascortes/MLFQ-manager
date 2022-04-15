#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
	/*Lectura del input*/
	char *file_name = (char *)argv[1];
	InputFile *input_file = read_file(file_name);

	/*Mostramos el archivo de input en consola*/
	printf("Nombre archivo: %s\n", file_name);
	printf("Cantidad de procesos: %d\n", input_file->len);
	printf("Procesos:\n");
	struct Queue *queue_a;
	struct Queue *queue_b;
	struct Queue *queue_c;
	struct Queue *processes;
	struct Queue *finished;

	queue_a = newQueue();
	queue_b = newQueue();
	queue_c = newQueue();
	processes = newQueue();
	finished = newQueue();


	Process *process;
	for (int i = 0; i < input_file->len; ++i)
	{
		process = newProcess(input_file->lines[i][0], atoi(input_file->lines[i][1]), atoi(input_file->lines[i][2]), atoi(input_file->lines[i][3]), atoi(input_file->lines[i][4]), atoi(input_file->lines[i][5]), atoi(input_file->lines[i][6]));
		//agregar procesos a queue processes

		enqueue(processes, process);
		printf("Creado: %s\n", process->name);
		// printf("Verificando: %s\n", *processes->head->name);
	}
	//code scheduler
	int cycle = 0;
	int quantum = atoi(argv[3]);
	printf("Inicia ciclo 0\n");
	printf("El quantum es %d\n", quantum);

	printQueue(processes);
	Process* new_process;

	int running = 0;


	while (finished->size < input_file->len){
		//comienzo ciclo
		//Añado un proceso si tiene que entrar
		new_process = startProcess(processes, cycle);
		while (new_process != NULL){
			printf("\nEntra a la lista A el proceso %s: \n", new_process->name);
			enqueue(queue_a, new_process);
			new_process =  startProcess(processes, cycle);
		}
		// revisar waitings finished y quantum 
		// printf("Cola A procesando %d size %d\n", queue_a->running, queue_a->size);
		// printf("Cola B procesando %d size %d\n", queue_b->running, queue_b->size);
		// printf("Cola C procesando %d size %d\n", queue_c->running, queue_c->size);
		// printf("Cola finished procesando %d size %d\n", finished->running, finished->size);
		actualizeRunning(queue_a, queue_b,finished, quantum*2);
		actualizeRunning(queue_b, queue_c,finished, quantum);
		actualizeRunning(queue_c, queue_c,finished, 100000); //hardcodeado para despues
		actualizeWaits(queue_a);
		actualizeWaits(queue_b);
		actualizeWaits(queue_c);

		if (queue_a->running || queue_b->running || queue_c->running){
			
		}
		else
		{
			if (readyProcesses(queue_a)){
			// printf("Empezamos a ejecutar cola A\n");
			}
			else if (readyProcesses(queue_b)){
				// printf("Empezamos a ejecutar cola B\n");
			}
			else if (readyProcesses(queue_c)){
				// printf("Empezamos a ejecutar cola C\n");
			}
		}

		// 
		actualizeCycle(queue_a);
		actualizeCycle(queue_b);
		actualizeCycle(queue_c);
		
		//final ciclo
		cycle += 1;
	}
	//Write csv
	FILE *fpt;
	fpt = fopen(argv[2], "w+");
	Process *temp;
	while (finished->size != 0){
		temp = dequeue(finished);
		fprintf(fpt,"%s, %d, %d, %d, %d, %d\n", 
		temp->name, 
		temp->cpu_times, 
		temp->interrupted_times, 
		temp->turnaround_time, 
		temp->response_time, 
		temp->waiting_time);
		free(temp);
	}


	// realese memory
	printf("Inicia liberacion de memoria\n");
	
	freeQueue(queue_a);
	freeQueue(queue_b);
	freeQueue(queue_c);
	freeQueue(processes);
	freeQueue(finished);
	input_file_destroy(input_file);
}
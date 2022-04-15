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
	printf("El quantum es %d\n", quantum);

	Process* new_process;

	int running = 0;


	while (finished->size < input_file->len){
		//comienzo ciclo
		//Añado un proceso si tiene que entrar
		new_process = startProcess(processes, cycle);
		while (new_process != NULL){
			enqueue(queue_a, new_process);
			new_process =  startProcess(processes, cycle);
		}
		// Revisar si deben volver a la cola A
		actualizeS(queue_a, queue_b);
		actualizeS(queue_a, queue_c);
		// revisar waitings finished y quantum 
		actualizeRunning(queue_a, queue_b,finished, quantum*2, cycle);
		actualizeRunning(queue_b, queue_c,finished, quantum, cycle);
		actualizeRunning(queue_c, queue_c,finished, 100000, cycle); //hardcodeado para despues
		actualizeWaits(queue_a);
		actualizeWaits(queue_b);
		actualizeWaits(queue_c);
	 	// Pasar procesos de READY a RUNNING
		if (!(queue_a->running || queue_b->running || queue_c->running)){

			if (!(readyProcesses(queue_a, cycle))){
				if (!(readyProcesses(queue_b, cycle))){
					readyProcesses(queue_c, cycle);
				}
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
		fprintf(fpt,"%s,%d,%d,%d,%d,%d\n", 
		temp->name, 
		temp->cpu_times, 
		temp->interrupted_times, 
		temp->turnaround_time, 
		temp->response_time, 
		temp->waiting_time);
		free(temp);
	}
	printf("Ejecuciones terminadas exitosamente\n");

	// realese memory
	printf("Inicia liberacion de memoria\n");
	
	freeQueue(queue_a);
	freeQueue(queue_b);
	freeQueue(queue_c);
	freeQueue(processes);
	freeQueue(finished);
	input_file_destroy(input_file);
}
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
	printf("Inicia ciclo 0\n");
	printQueue(processes);
	Process* new_process;
	while (cycle <= 10){
		//comienzo ciclo
		//Añado un proceso si tiene que entrar
		new_process = startProcess(processes, cycle);

		while (new_process != NULL){
			printf("\nEntra a la lista A el proceso %s: \n", new_process->name);
			enqueue(queue_a, new_process);
			new_process =  startProcess(processes, cycle);
		}
		//final ciclo
		cycle += 1;
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
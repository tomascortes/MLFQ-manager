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
	node* processes = NULL;
	node* temp;	

	for (int i = 0; i < input_file->len; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			printf("%s ", input_file->lines[i][j]);
		}
		temp = create_node(input_file->lines[i][0]);

		if (processes == NULL){
			processes = temp;
		}
		else{
			add_node(processes, temp);
		}
		printf("-\n");
	}
	print_list(processes);
	//code scheduler

	
	

	// realese memory
	// node_destroy(queue_1);
	input_file_destroy(input_file);
}
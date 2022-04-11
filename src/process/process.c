#include "process.h"


Process* newProcess(
    char* name,
    int pid, 
    int start_cycle, 
    int cycles,
    int wait,
    int wait_delay, 
    int s)
{
	Process *pro;
	pro = malloc(sizeof(Process));

	// if (pro == NULL) {
	// 	return pro;
	// }

    pro-> name = name; 
    pro-> pid = pid;
    pro-> start_cycle = start_cycle;
    pro-> cycles = cycles; //cuantos ciclos de CPU requiere
    pro-> wait = wait; //tiempo en CPU
    pro-> wait_delay = wait_delay; 
    pro-> s = s;

    // variables aux
    pro -> used_cycles = 0; // (acumulado) cuantos lleva ejecutando
    pro -> used_waits = 0;
    pro -> used_delay = 0;
    pro -> used_s = 0;
    pro -> status = READY;

    //output
    pro -> cpu_times = 0;
    pro -> interrupted_times = 0;
    pro -> turnaround_time = 0;
    pro -> response_time = 0;
    pro -> waiting_time = 0;

	return pro;
}
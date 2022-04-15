#pragma once

typedef enum Status
{
  READY,
  WAITING,
  FINISHED,
  RUNNING,
} Status;

typedef struct Process{
    char* name; 
    int pid;
    int start_cycle;
    int cycles; //cuantos ciclos de CPU requiere
    int wait; //tiempo en CPU
    int wait_delay; 
    int s;

    // variables aux
    int used_cycles; // (acumulado) cuantos lleva ejecutando
    int used_waits;
    int used_delay;
    int used_s;
    Status status;
    int quantum;

    //output
    int cpu_times;
    int interrupted_times;
    int turnaround_time;
    int response_time;
    int waiting_time; // Ready + waiting
 }Process;

// extern int readyProcesses(struct Queue *q);
extern Process* newProcess(char* name,    int pid,     int start_cycle,     int cycles,    int wait,    int wait_delay,     int s);
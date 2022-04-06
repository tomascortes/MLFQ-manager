#pragma once

typedef enum
{
  READY = 0,
  WAITING = 1,
  FINISHED = 2,
} Status;

typedef struct Process{
    int pid;
    char name[32]; 
    Status status; 
    int cpu_usage_rounds;
    int interruptions;
    int turn_araound_time;
    int response_time;
    int waiting_time;
 };
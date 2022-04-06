#pragma once
#include "../process/process.h"


/** Nodo de ligada de objetos en una celda */
typedef struct node
{
  struct node* next;
  int process;
} Node;



typedef struct Queue
{
  Node* first;
} Queue;

Node* node_init(int process);
void node_destroy(Node* node);
void print_list(Node* first);
void add_node(Node* first, Node* new_node);
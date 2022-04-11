#pragma once
#include "../process/process.h"


typedef struct node{
    int begin;
    char* name;
    struct node *next; 
}node;

/** Nodo de ligada de objetos en una celda */
// typedef struct node
// {
//   struct node* next;
//   int process;
// } Node;



// typedef struct Queue
// {
//   Node * node;
// } Queue;

// Node * node_init(int process);
// void node_destroy(Node* node);
// void print_list(Node* first);
// void add_node(Node* first, Node* new_node);

node* create_node(char* nombre);
void print_list(node* first);
void add_node(node* first, node* new_node);
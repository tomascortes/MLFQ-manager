#include "queue.h"
#include "../process/process.h"
#include <stdio.h>



Node* node_init(int process)
{
  // Creo la celda
  Node* node = malloc(sizeof(Node));

  // Inicializo sus variables
  node -> next = NULL;
  node -> process = process;

  // Retorno la celda
  return node;
}



void print_list(Node* first) {
   Node *ptr = first;
   while(ptr != NULL) {
      printf("Nombre: %s \n", first->process);
      ptr = ptr->next;
   }
}

void add_node(Node* first, Node* new_node) {
   Node *ptr = first;
   while(ptr -> next != NULL) {
      ptr = ptr->next;
   }
   ptr -> next = new_node;
}

void node_destroy(Node* node)
{
  if (node)
  {
    node_destroy(node -> next);
    free(node);
  }
}
#include "queue.h"
#include "../process/process.h"
#include <stdio.h>

// typedef struct LinkedList *nodo

node *create_node(char* nombre){
    node *newNode = malloc(sizeof(node));
    newNode->begin = 0;
    newNode->name = nombre;
    newNode->next = NULL;
    return newNode;
}


void print_list(node* first) {
   node *ptr = first;
   printf("\n[ \n");
  //  printf("Nombre: %s \n", first->name);
   //start from the beginning
   while(ptr != NULL) {
      printf("Nombre: %s \n", ptr->name);
      ptr = ptr->next;
   }
   printf(" ]");
}

node* add_node(node* first, node* new_node) {
   if (first ==  NULL){
      first = new_node;
      return new_node;
   }

   node *ptr = first;
   //start from the beginning
   while(ptr->next != NULL) {
      ptr = ptr->next;
   }
   ptr->next = new_node;
   return first;

}

// Node* node_init(int process)
// {
//   // Creo la celda
//   Node* node = malloc(sizeof(Node));

//   // Inicializo sus variables
//   node -> next = NULL;
//   node -> process = process;

//   // Retorno la celda
//   return node;
// }



// void print_list(Node* first) {
//    Node *ptr = first;
//    while(ptr != NULL) {
//       printf("Nombre: %d \n", first -> process);
//       ptr = ptr->next;
//    }
// }

// void add_node(Node *first, Node *new_node) {
//    Node *ptr = first;
//    while(ptr -> next != NULL) {
//       ptr = ptr->next;
//       printf("Siguente nodo: %d", ptr -> process);
//    }
//    printf("Termino de recorrer la lista");
//    ptr -> next = new_node;
// }

// void node_destroy(Node* node)
// {
//   if (node)
//   {
//     node_destroy(node -> next);
//     free(node);
//   }
// }
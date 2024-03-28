#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * lista = (List *)malloc(sizeof(List));
  lista -> head = NULL;
  lista -> tail = NULL;
  lista -> current = NULL;
  return lista;
}

void * firstList(List * list) {
  if (list == NULL || list -> head == NULL){
    return NULL;
  }
  list-> current = list -> head;
  return (void *)list -> current -> data;
}

void * nextList(List * list) {
  if (list == NULL || list -> current == NULL || list -> current -> next == NULL){
    return NULL;
  }
  else{
    list -> current = list -> current -> next;
    return (void *)list -> current -> data;
  }
}

void * lastList(List * list) {
  if (list == NULL)
    return NULL;
  else{
    while (list -> current -> next != NULL){
      list->current = list->current->next;
    }
  }
  return (void *)list -> current -> data;
}

void * prevList(List * list) {
  if (list == NULL || list -> current == NULL || list -> current -> prev == NULL){
    return NULL;
  }
  else{
    Node * aux = list->current->prev;
    list->current = aux;
    }
  return (void *)list -> current -> data;
}

void pushFront(List * list, void * data) {
  if (list == NULL)
    return;
  Node * newNode = createNode(data);
  newNode -> next = list->head;
  if (list->head) list->head->prev = newNode;
  list->head = newNode;
}

void pushBack(List * list, void * data) {
  if (list == NULL)
    return;
  Node * aux = list->head;
  while (aux -> next != NULL){
    aux = aux -> next;
  }
  Node * newNode = createNode(data);
  aux -> next = newNode;
  newNode->prev = aux;
  list->tail = newNode;
}

void pushCurrent(List * list, void * data) {
  Node * newNode = createNode(data);
  newNode->prev = list->current;
  newNode->next = list->current->next;
  newNode->prev->next = newNode;
  newNode->next->prev = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
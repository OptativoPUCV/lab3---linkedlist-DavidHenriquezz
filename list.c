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
  list->head = newNode;
}

void pushBack(List * list, void * data){
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * newNode = createNode(data);
  newNode->prev = list->current;
  newNode->next = list->current->next;
  list->current->next = newNode;
  if (newNode->next) newNode->next->prev = newNode;
  else list->tail = newNode;
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
  Node * izq = list->current->prev;
  Node * der = list->current->next;
  if (list->head == list->current){
    list->head = list->current->next;
    list->head->prev = NULL;
    list->head->next = der->next;
  }
  else if(list->tail == list -> current){
    list->tail = list->current->prev;
    list->tail->next = NULL;
    list->tail->prev = izq->prev;
  }
  else{
    izq->next = der;
    der->prev = izq;
  }
  void * data = list->current->data;
  free(list->current);
  list->current = NULL;
  return data; 
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
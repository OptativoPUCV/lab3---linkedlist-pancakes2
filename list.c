#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->current = NULL;
  list->tail = NULL;
  return list;
}

void *firstList(List *list) {
    if (list->head == NULL) {return NULL;}
    list->current = list->head;
    return list->current->data;
}

void *nextList(List *list) {
    if (list->current == NULL || list->current->next == NULL) {return NULL;}
    list->current = list->current->next;
    return list->current->data;
}

void *prevList(List *list) {
    if (list->current == NULL || list->current->prev == NULL) {return NULL;}
    list->current = list->current->prev;
    return list->current->data;
}

void *lastList(List *list) {
    if (list->head == NULL) {return NULL;}
    list->current = list->tail;
    return list->current->data;
}

void pushCurrent(List *list, void *data) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {return NULL;}
    newNode->data = data;
    newNode->next = list->current->next;
    newNode->prev = list->current;
    if (list->current->next != NULL) {
        list->current->next->prev = newNode;
    }
    list->current->next = newNode;
    list->current = newNode;
    if (list->tail == list->current->prev) {
        list->tail = newNode;
    }
}

void pushFront(List *list, void *data) {
    list->current = list->head;
    pushCurrent(list, data);
    if (list->head == NULL) {
        list->head = list->current;
    }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) { return NULL; }

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}
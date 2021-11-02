#include <stdio.h>
#include "list.h"

//retrive a process from the list array
Process *get(Process **list, int id, int len) {
  if (list == NULL || id < 1)
    return NULL;

  for (int i = 0; i < len; i++)
    if (list[i] != NULL && list[i]->id == id)
      return list[i];

  return NULL;
}

//remove a process from the list array
void pop(Process **list, Process *element, int len) {
	if (list == NULL || element == NULL)
    return;

  for (int i = 0; i < len; i++)
    if (list[i] != NULL && list[i]->id == element->id) {
    	list[i] = NULL;
    	return;
    }
}

//add a process to the list array
void push(Process **list, Process *element, int i) {
  if (list == NULL || element == NULL)
    return;

   list[i] = element;
}

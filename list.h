// prevents header file from being processed twice
#ifndef LIST_H_
#define LIST_H_

typedef struct Process {
  int id;
  int burst;
  int priority;
  int waittime;
} Process;

Process* get(Process **list, int id, int len);

void pop(Process **list, Process *element, int len);

void push(Process **list, Process *element, int i);

#endif

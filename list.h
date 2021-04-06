// prevents header file from being processed twice
#ifndef LIST_H_
#define LIST_H_

typedef struct Process {
  int id;
  int burst;
  int priority;
  int throughput;
} Process;

Process *get(Process **list, int len, int id);

void put(Process **list, int len, Process *element);

#endif

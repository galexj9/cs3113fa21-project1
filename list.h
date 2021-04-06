// prevents header file from being processed twice
#ifndef LIST_H_
#define LIST_H_

typedef struct Process {
  int id;
  int burst;
  int priority;
  int throughput;
} Process;

#endif

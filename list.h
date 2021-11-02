//prevents header file from being processed twice
#ifndef LIST_H_
#define LIST_H_

typedef struct Process {
	int id;
	int burst;
	int priority;
	int waittime;
	struct Process* next;
} Process;

//push a node to the end of a list
extern Process* push(Process* head, Process* element);

//sorts the list in descending order using mergesort
extern void sort(Process** list);
#endif

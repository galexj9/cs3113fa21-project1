#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void print(FILE* fp, Process* l);

/* Simulate a process dispatcher and calculate
** some relevant statistics */
int main(int argc, char **argv) {
  // select file from first arg or use stdin
  FILE *infp = (argc == 2) ? fopen(argv[1], "r") : stdin;
  FILE *outfp = (argc == 3) ? fopen(argv[2], "r") : stdout;

  // Get formatted info from stdin
  int processors, threads, instructions;
  fscanf(infp, "%d%d%d", &processors, &threads, &instructions);

  if (!processors || !threads || !instructions ||
  		instructions < 1 || threads < 1 || processors != 1) {
    fprintf(stderr, "Invalid input.\n");
    exit(-1);
  }

  // create a linked list to keep track of process ids
  Process **pList = malloc(sizeof(Process *));

	// total statitics to track
  int volSwitch = 0, involSwitch = 0, nonSwitch = 0;
  float throughput = 0, turnaround = 0, waiting = 0;
  float response = 0, cpuUtilization = 100;

	//build the list of processes
	Process* prev = NULL;
  for (int i = 0; i < instructions; i++) {
    Process *proc = (Process *) malloc(sizeof(Process));
    fscanf(infp, "%d%d%d", &proc->id, &proc->burst, &proc->priority);
    proc->waittime = throughput;

		//track the number of times the context doesn't switch
		if (prev && prev->id == proc->id)
			nonSwitch += 1;

		throughput += proc->burst;
		turnaround += throughput;

		*pList = push(*pList, proc);
		prev = proc;
	}

  //sort processes by id and in order submitted
	sort(pList);

  Process* proc = *pList;
	Process* prevProc = NULL;
	waiting += proc->waittime;
	response += proc->waittime;

	//loop thru the sorted list starting with the 2nd element
	for (int i = 1; i < instructions; i++) {
		prevProc = proc;
		proc = proc->next;

		//if the process is continuing
		if (prevProc->id == proc->id) {
			//add time spent waiting since last run and remove old run's completion time
			waiting += proc->waittime - (prevProc->waittime + prevProc->burst);
			turnaround -= prevProc->waittime + prevProc->burst;
		}
		//first time a process runs record its wait and reponse times
		else {
			waiting += proc->waittime;
			response += proc->waittime;
		}
	//fprintf(stderr, "process: %d, turnaround: %05.2f, waiting: %05.2f, response: %05.2f\n", proc->id, turnaround, waiting, response);
	}

	volSwitch = threads;
	involSwitch = instructions - threads - nonSwitch;

  // average the stats
  throughput = (throughput) ? threads / throughput : 0;
  turnaround /= threads;
  waiting /= threads;
  response /= threads;

  /* Output the Scheduler Stats:
  ** Voltary Context Switches			  (# of times switching to a new process)
  ** Non-Voluntary Context Switches (# of times returning to a process)
  ** Average Througput     					(avg time to process instruction)
  ** Average Waiting Time  					(time on ready queue)
  ** Average Response Time 					(time untill started) */
  fprintf(outfp, "%d\n%d\n", volSwitch, involSwitch);
  fprintf(outfp, "%0.2f\n", cpuUtilization);
  fprintf(outfp, "%0.2f\n%0.2f\n%0.2f\n%0.2f\n", throughput, turnaround, waiting, response);
  return 0;
}

void print(FILE *fp, Process* l) {
	while (l) {
		fprintf(fp, "Process %d burst %d priority %d\n", l->id, l->burst, l->priority);
		l = l->next;
	}
}

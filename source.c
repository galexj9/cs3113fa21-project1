#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Simulate a process dispatcher and calculate
** some relevant statistics */
int main(int argc, char **argv) {
  // select file from arg or use stdin
  FILE *fp = (argc == 2)? fopen(argv[1], "r") : stdin;

  // Extract the formatted info from stdin
  int processors, threads, instructions;
  fscanf(fp, "%d%d%d", &processors, &threads, &instructions);

	if(!processors || !threads || !instructions){
		printf("Invalid input");
		exit(-1);
	}
	
  // create a list to keep track of processed ids
  Process **pList = malloc(sizeof(Process *) * instructions);

  int volSwitch = 0, involSwitch = 0;
  float throughput = 0, turnaround = 0, waiting = 0;
  float response = 0, cpuUtilization = 100;

	// Build the process ready queue
	float waittime = 0;
	for(int i = 0; i < instructions; i++) {
    Process *proc = (Process *) malloc(sizeof(Process));
    fscanf(fp, "%d%d%d", &proc->id, &proc->burst, &proc->priority);
    proc->waittime = waittime;
    waittime += proc->burst;

    pList[i] = proc;
  }

	//Loop through the instructions
  for(int i = 0; i < instructions; i++) {
		Process *proc = pList[i];
		Process *oldProc = get(pList, instructions, proc->id);
		
		if(i == 0 || proc->id != pList[i-1]->id) {
			volSwitch += 1;
			waiting += throughput;
		}

		if(oldProc != NULL && oldProc != proc) {
		  if (oldProc != pList[i-1]) {
				volSwitch -= 1;
				involSwitch += 1;
			}
			//only add the first time a process is called's wait time
			turnaround -= proc->waittime;
			//remove the oldProc so the next get() returns the prev proccess
			pop(pList, instructions, oldProc);
		} else {
			response += throughput;
		}

    // Calculate throughput as (total burst time) / (number of instructions)
    throughput += proc->burst;
    // add total burst+wait time for the process to turnaround
    turnaround += throughput;
  }

  // average the stats
  throughput = (throughput)? threads / throughput : 0;
  turnaround /= threads;
  waiting /= threads;
  response /= threads;

  /* Output the Scheduler Stats:
  ** Voltary Context Switches
  ** Non-Voluntary Switches
  ** Average Througput
  ** Average Waiting Time
  ** Average Response Time */
  printf("%d\n%d\n", volSwitch, involSwitch);
  printf("%0.2f\n", cpuUtilization);
  printf("%0.2f\n", throughput);
  printf("%0.2f\n%0.2f\n%0.2f\n", turnaround, waiting, response);

  return 0;
}

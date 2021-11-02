#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

  // create an array to keep track of processed ids
  Process **pList = malloc(sizeof(Process *) * instructions);

	// total statitics to track
  int volSwitch = 0, involSwitch = 0;
  float throughput = 0, turnaround = 0, waiting = 0;
  float response = 0, cpuUtilization = 100;
	Process* prev = NULL;

  // Loop through the instructions
  for (int i = 0; i < instructions; i++) {

    // scan in a new process to dispatch
    Process *proc = (Process *)malloc(sizeof(Process));
    fscanf(infp, "%d%d%d", &proc->id, &proc->burst, &proc->priority);
    proc->waittime = throughput;

    //get the first instance of any continuing process
    Process *oldProc = get(pList, proc->id, instructions);

    // if the context switched
    if (!prev || proc->id != prev->id)
    	if (oldProc != NULL)
    		involSwitch += 1;
    	else
    		volSwitch += 1;

		//if this is the first time processing a thread
    if (oldProc == NULL) {
			waiting += throughput;
			response += throughput;
		} else {
			// add the time spent waiting since the previous proccess ran
			waiting += throughput - (oldProc->waittime + oldProc->burst);
			// sub the old turnaround time since the old process was not completed
			turnaround -= oldProc->waittime + oldProc->burst;
			//remove the old proc from the list so get() returns only the prev proc
      pop(pList, oldProc, instructions);
		}

    // add process runtime to throughput and proccess completion time to turnaround
    turnaround += throughput + proc->burst;
    throughput += proc->burst;
    push(pList, proc, i);
    prev = proc;

 		//fprintf(stderr, "process: %d, throughput: %05.2f, turnaround: %05.2f, waiting: %05.2f, response: %05.2f, instruction: %d\n", proc->id, throughput, turnaround, waiting, response, i);
		//fprintf(stderr, "process: %d, vol: %d, invol: %d\n", proc->id,  volSwitch, involSwitch);
  }
	//fprintf(stderr, "averages:   throughput: %05.2f, turnaround: %05.2f, waiting: %05.2f, response: %05.2f\n", throughput, waiting, response, turnaround);

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

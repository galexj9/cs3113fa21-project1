#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Simulate a process dispatcher and calculate
** some relevant statistics */
// Uses a formatted file to stdin for the processes
/* <Number of Processes Available to Run>
** <Number of Execution Elements "contexts"> <Number of instructions to
*schedule>
** <pid> <burst time> <priority>... */
int main() {
  // Extract the formatted info from stdin
  int processors, threads, instructions;
  scanf("%d", &processors);
  scanf("%d", &threads);
  scanf("%d", &instructions);

  // create a list to keep track of processed ids
  Process **pList = malloc(sizeof(Process *) * threads);
  for (int i = 0; i < threads; i++)
    pList[i] = malloc(sizeof(Process));

  int volSwitch = 0, involSwitch = 0, id = 0;
  float throughput = 0, turnaround = 0, waiting = 0;
  float response = 0, cpuUtilization = 100;

  // scan through stdin for processes
  int prevID = 0;
  while (scanf("%d", &id) != EOF) {
    Process *proc = (Process *)malloc(sizeof(Process));
    scanf("%d", &proc->burst);
    scanf("%d", &proc->priority);
    proc->id = id;
    proc->turnaround = throughput + proc->burst;

    if (prevID != proc->id) {
      volSwitch++;

      // time on ready queue (not burst time)
      waiting += throughput;

      if (get(pList, threads, proc->id) != NULL) {
        volSwitch--;
        involSwitch++;
      } else {
        response += throughput;
        put(pList, threads, proc);
      }
    }

    Process *oldProc = get(pList, threads, proc->id);
    if (oldProc != NULL)
      turnaround -= oldProc->turnaround;

    // Calculate throughput as (total burst time) / (number of instructions)
    throughput += proc->burst;
    // add total burst+wait time for the process to turnaround
    turnaround += throughput; //(wait + burst time) (subtract duplicate threads)

    prevID = proc->id;
  }

  // average the stats
  throughput = threads / throughput;
  turnaround /= threads;
  waiting /= threads;
  response /= threads;

  /* Output the Scheduler Stats:
  ** Voltary Context Switches
  ** Non-Voluntary Switches
  ** Average Througput
  ** Average Waiting Time
  ** Average Response Time */
  printf("## Output Stats ##\n");
  printf("%d\n%d\n", volSwitch, involSwitch);
  printf("%0.2f\n", cpuUtilization);
  printf("%0.2f\n%0.2f\n%0.2f\n%0.2f\n", throughput, turnaround, waiting,
         response);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Simulate a process dispatcher and calculate
** some relevant statistics */
int main(int argc, char **argv) {
  // select file from arg or use stdin
  File *fp = (argc) ? fopen(argv[0], "r") : stdin;

  // Extract the formatted info from stdin
  int processors, threads, instructions;
  scanf("%d", &processors);
  scanf("%d", &threads);
  scanf("%d", &instructions);

  // create a list to keep track of processed ids
  Process **pList = malloc(sizeof(Process *) * threads);

  int volSwitch = 0, involSwitch = 0, id = 0;
  float throughput = 0, turnaround = 0, waiting = 0;
  float response = 0, cpuUtilization = 100;

  // scan through stdin for processes
  int prevID = 0;
  while (fscanf(fp, "%d", &id) != EOF) {
    Process *proc = (Process *)malloc(sizeof(Process));
    fscanf(fp, "%d", &proc->burst);
    fscanf(fp, "%d", &proc->priority);
    proc->id = id;
    proc->turnaround = throughput + proc->burst;

    // only count turnaround of processes the final time they complete
    Process *oldProc = get(pList, threads, proc->id);
    if (oldProc != NULL)
      turnaround -= oldProc->turnaround;

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

    // Calculate throughput as (total burst time) / (number of instructions)
    throughput += proc->burst;
    // add total burst+wait time for the process to turnaround
    turnaround += throughput;

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
  fprintf(fp, "%d\n%d\n", volSwitch, involSwitch);
  fprintf(fp, "%0.2f\n", cpuUtilization);
  fprintf(fp, "%0.2f\n", throughput);
  fprintf(fp, "%0.2f\n%0.2f\n%0.2f\n", turnaround, waiting, response);

  return 0;
}

#include <stdio.h>

int contains(int *list, int len, int el);
void put(int *list, int len, int el);

/* Simulate a process dispatcher and calculate
** some relevant statistics */
// Uses a formatted file to stdin for the processes
/* <Number of Processes Available to Run>
** <Number of Execution Elements "contexts"> <Number of instructions to
*schedule>
** <pid> <burst time> <priority> */
int main() {
  // Extract the formatted info from stdin
  int processors, threads, instructions;
  int *processed;
  scanf("%d", &processors);
  scanf("%d", &threads);
  scanf("%d", &instructions);
  processed = (int *)malloc(sizeof(int) * threads);
  memset(processed, -1, (sizeof(int)) * threads);

  int volSwitch = 0, involSwitch = 0, proc = 0, prevProc = 0;
  float throughput = 0, turnaround = 0, waiting = 0, response = 0,
        cpuUtilization = 100;

  while (scanf("%d", &proc) != EOF) {
    int burst, priority;
    scanf("%d", &burst);
    scanf("%d", &priority);

    if (proc != prevProc) {
      volSwitch++;
      waiting += throughput;
    }

    if (contains(processed, (sizeof(int)) * threads, proc) == -1) {
      response += throughput; // change response time for ALL prev mentions
      put(processed, (sizeof(int)) * threads, proc);
    }

    // cpu utilization is always 100 for 1 processor
    // Calculate throughput as (total burst time) / (number of instructions
    throughput += burst;
    // turnaround is time from submission to completion
    turnaround += throughput;

    prevProc = proc;
    printf("Running process: %d %d %d\n", proc, burst, priority);
  }

  throughput = instructions / throughput;
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

int contains(int *list, int len, int el) {
  for (int i = 0; i < len; i++)
    if (list[i] == el)
      return 1;
  return -1;
}

void put(int *list, int len, int el) {
  for (int i = 0; i < len; i++) {
    if (list[i] == -1) {
      list[i] = el;
      break;
    }
  }
}
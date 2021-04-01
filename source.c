#include <stdio.h>

/* Simulate a process dispatcher and calculate
** some relevant statistics */
// Uses a formatted file to stdin for the processes
/* <Number of Processes Available to Run>
** <Number of Execution Elements "contexts"> <Number of instructions to
*schedule>
** <pid> <burst time> <priority> */
int main() {
  // Extract the formatted info from stdin
  int processors, threads, instructions, p;
  processors = getchar();
  threads = getchar();
  instructions = getchar();

  int volSwitch = 0, involSwitch = 0;
  float throughput = 0, turnaround = 0, waiting = 0, response = 0,
        cpuUtilization = 100;

  while ((p = getchar()) != NULL) {
    int burst = getchar();
    int priority = getchar();

    throughput += burst;
  }

  throughput /= threads;

  /* Output the Scheduler Stats:
  ** Voltary Context Switches
  ** Non-Voluntary Switches
  ** Average Througput
  ** Average Waiting Time
  ** Average Response Time */
  printf("%d\n%d\n", volSwitch, involSwitch);
  printf("%0.2f\n", cpuUtilization);
  printf("%0.2f\n%0.2f\n%0.2f\n", throughput, waiting, response);

  return 0;
}
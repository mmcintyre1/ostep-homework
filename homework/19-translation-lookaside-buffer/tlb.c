#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1000000000L

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf("Usage: %s <int: pages> <int: trials>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  cpu_set_t set;
  CPU_ZERO(&set);    // clear cpu mask
  CPU_SET(0, &set);  // set cpu 0
  if (sched_setaffinity(0, sizeof(cpu_set_t), &set)) {
    fprintf(stderr, "Error setting cpu affinity\n");
    exit(EXIT_FAILURE);
  }

  int num_pages = strtol(argv[1], NULL, 10);
  int num_trials = strtol(argv[2], NULL, 10);

  long PAGESIZE = sysconf(_SC_PAGESIZE);
  int jump = PAGESIZE / sizeof(int);
  int *array = calloc(num_pages, PAGESIZE);
  struct timespec start, end;

  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1) {
    perror("clock gettime");
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < num_trials; j++) {
    for (int i = 0; i < num_pages * jump; i += jump) array[i] += 1;
  }

  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1) {
    perror("clock gettime");
    exit(EXIT_FAILURE);
  }

  // get elapsed time in nanoseconds
  double elapsed =
      (end.tv_sec - start.tv_sec) * 1E9 + (end.tv_nsec - start.tv_nsec);

  // multiply elapsed by number of trials and count of pages, which will
  // give us the time spent per page access
  printf("%f\n", elapsed / (num_trials * num_pages));

  free(array);
  return 0;
}

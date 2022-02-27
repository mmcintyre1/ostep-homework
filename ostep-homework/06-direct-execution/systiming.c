#include <stdio.h>
#include <time.h>
#include <unistd.h>

void timing_clock(void) {
  clock_t start, end;
  start = clock();
  read(0, NULL, 0);
  end = clock();
  double cpu_time_used = ((double)(end - start));
  printf("clock timing: %g nanoseconds\n", cpu_time_used);
}

void timing_clock_gettime(void) {
  struct timespec start, end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  read(0, NULL, 0);
  clock_gettime(CLOCK_MONOTONIC, &end);
  double cpu_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
  printf("clock_gettime timing: %g nanoseconds\n", cpu_time);
}

int main() {
  timing_clock();
  timing_clock_gettime();
  return 0;
}
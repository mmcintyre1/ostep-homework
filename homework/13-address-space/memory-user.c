#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: memory-user <memory> <time>\n");
    exit(EXIT_FAILURE);
  }

  printf("pid: %d\n", getpid());

  long memory = strtol(argv[1], NULL, 10) * 1024 * 1024;
  int end = (int)strtol(argv[2], NULL, 10);

  clock_t start = clock();
  int *arr = (int *)malloc(sizeof(int) * memory);

  printf("mem: %lu bytes\n", memory);
  printf("clock start: %lu\n", start);

  if (arr == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    double time_spent = ((double)clock() - start) / CLOCKS_PER_SEC;
    if (time_spent >= end) break;
    for (int i = 0; i < (long)(memory / (sizeof(int))); i++) arr[i] = 1;
  }

  free(arr);
  return 0;
}
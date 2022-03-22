#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *data = (int *)malloc(101);
  data[100] = 5;
  free(&data[50]);
  printf("%d\n", data[50]);
  return 0;
}

#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *data = (int *)malloc(101);
  data[100] = 5;
  free(data);
  printf("%d\n", data[100]);
  return 0;
}

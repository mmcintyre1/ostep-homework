#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }

    char buf[BUFSIZ];
    while (fgets(buf, sizeof buf, fp)) {
      printf("%s", buf);
    }

    fclose(fp);
  }
  return 0;
}

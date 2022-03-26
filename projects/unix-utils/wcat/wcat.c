#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      fprintf(stderr, "wcat: cannot open %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }

    char buf[BUFSIZ];
    while (fgets(buf, sizeof buf, fp)) {
      printf("%s", buf);
    }

    fclose(fp);
  }
  return 0;
}

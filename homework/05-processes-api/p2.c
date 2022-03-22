#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_or_die()
{
  int rc = fork();
  assert(rc >= 0);
  return rc;
}

int main(int argc, char *argv[])
{
  FILE *fd = fopen("tmp.txt", "w");

  if (fd == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  int rc = fork_or_die();

  if (rc == 0)
  {
    fprintf(fd, "child - pid:%d\n", (int)getpid());
  }
  else
  {
    fprintf(fd, "parent - pid:%d\n", (int)getpid());
  }
  fclose(fd);
  return 0;
}

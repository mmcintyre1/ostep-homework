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
  int rc = fork_or_die();

  if (rc == 0)
  {
    printf("hello\n");
  }
  else
  {
    sleep(6);
    printf("goodbye\n");
  }
  return 0;
}

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

int wait_or_die()
{
  int rc = wait(NULL);
  return rc;
}

int main(int argc, char *argv[])
{
  printf("parent pid:%d\n", (int)getpid());
  int rc = fork_or_die();
  if (rc < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (rc == 0)
  {
    printf("child pid:%d\n", (int)getpid());
    int c_wrc = wait_or_die();
    printf("child wait result code: %d\n", c_wrc);
  }
  else
  {
    int p_wrc = wait_or_die();
    printf("parent wait result code: %d\n", p_wrc);
  }
  return 0;
}

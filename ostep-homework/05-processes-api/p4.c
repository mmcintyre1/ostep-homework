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

void wait_or_die()
{
  int rc = wait(NULL);
  assert(rc > 0);
}

int main(int argc, char *argv[])
{
  int rc = fork_or_die();

  if (rc < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (rc == 0)
  {
    char *my_args[2] = {"ls", NULL};
    execvp("ls", my_args);
  }
  else
  {
    wait_or_die();
  }
  return 0;
}

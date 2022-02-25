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
  int x = 0;
  printf("parent - pid:%d, x:%d\n", (int)getpid(), x);
  int rc = fork_or_die();
  if (rc == 0)
  {
    // child
    printf("before setting child - pid:%d, x:%d\n", (int)getpid(), x);
    x = 1;
    printf("after setting child - pid:%d, x:%d\n", (int)getpid(), x);
  }
  else
  {
    // parent
    printf("before setting parent - pid:%d, x:%d\n", (int)getpid(), x);
    x = 3;
    printf("after setting parent - pid:%d, x:%d\n", (int)getpid(), x);
  }
  printf("pid:%d, x:%d\n", (int)getpid(), x);
  return 0;
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_or_die() {
  int rc = fork();
  assert(rc >= 0);
  return rc;
}

void wait_or_die() {
  int rc = wait(NULL);
  assert(rc >= 0);
}

int main(int argc, char* argv[]) {
  int pipefd[2];
  char buf;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  int rc = fork_or_die();

  if (rc < 0) {
    perror("fork failed");
    exit(1);
  }

  else if (rc == 0) {
    close(pipefd[1]);

    while (read(pipefd[0], &buf, 1) > 0) {
      write(STDOUT_FILENO, &buf, 1);
    }

    write(STDOUT_FILENO, "\n", 1);
    close(pipefd[0]);
    _exit(EXIT_SUCCESS);
  }

  else {
    close(pipefd[0]); /* Close unused read end */
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]); /* Reader will see EOF */
    wait(NULL);       /* Wait for child */
    exit(EXIT_SUCCESS);
  }

  return 0;
}

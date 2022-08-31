# 5 - Process API
- **process identifier** - aka PID, used to identify a process
- the separation of fork and exec enables features like input/output redirection, pipes, and other cool features

## the fork system call
- used to create a new process
- creates _almost an exact copy_ of the parent process as a child process, key difference is PID
- not _deterministic_, as the parent or child might finish executing first
- if you want to implement _determinism_, you implement a call to wait for the parent

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char*argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {         // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {              // parent goes down this path (main)
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
    rc, rc_wait, (int) getpid());
    }
    return 0;
}
```

## the wait system call
- allows a parent to wait for its child to complete execution.
- a way to introduce determinism into parent/child execution

## the exec system call
- useful when you want to run a program that is different from the calling program

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char*argv[]) {
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        // now exec "wc"...
        char*myargs[3];
        myargs[0] = strdup("wc");   // program: wc (word count)
        myargs[1] = strdup("p4.c"); // arg: file to count
        myargs[2] = NULL;           // mark end of array
        execvp(myargs[0], myargs);  // runs word count
    } else {
        // parent goes down this path (main)
        int rc_wait = wait(NULL);
    }
    return 0;
}
```

## Process Control
- available in the form of signals which can cause jobs to stop, continue, or terminate
- which processes can be controlled by whom is encapsulated in the idea of a user -- a user can only control their own processes
- a superuser can control all processes, as well as other privileged actions

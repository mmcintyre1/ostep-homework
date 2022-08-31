## Homework (Simulation)

[README on fork.py](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-api/README-fork.md)

1. Run `./fork.py -s 10` and see which actions are taken. Can you predict what the process tree looks like at each step? Use the `-c` flag to check your answers. Try some different random seeds (`-s`) or add more actions (`-a`) to get the hang of it.

All processes should be leaves off of the first process, process a.

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/05-processes-api (master)$ python3 fork.py -s 10 -c

ARG seed 10
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

2. One control the simulator gives you is the `fork.percentage`, controlled by the `-f` flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., `-a 100`) and vary the `fork.percentage` from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with `-c`.

The higher the percentage, the more complicated the process tree will end up. At 0.1, you won't have many child processes spawning off of process a, but as you approach 0.9 and above, the process tree depth will increase commensurately.

3. Now, switch the output by using the `-t` flag (e.g., `run./fork.py -t`). Given a set of process trees, can you tell which actions were taken?

It's pretty easy when the process tree is simple to compare the current process tree to the previous one and see what has been added or removed (process forked or killed).

4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`.This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the `-R` flag? Learn more about what happens to orphaned processes on your own to add more context.

When the process c exits, I would expect all its child processes to be killed recursively as well. If we pass in the `-R` imperative, I would expect the children of c to be attached to the parent node, process a.

First, running `-A a+b,b+c,c+d,c+e,c- -c`

```console
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```

Then, `-A a+b,b+c,c+d,c+e,c- -c -R`

```console
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```

Turns out in the first example the child processes don't get killed but are moved to the root node. Passing in `-R` just uses process b instead of the root, which is the closest parent to child processes under process c.

5. One last flag to explore is the `-F` flag, which skips intermediate steps and only asks to fill in the final process tree. Run `./fork.py -F` and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.

It's straightforward to walk the process actions and create a final tree.

6. Finally, use both `-t` and `-F` together. This shows the final process tree, but then asks you to fill in the actions that took place. By look-ing at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

It's pretty difficult to tell more information than how many processes were created and what exited. The fewer processes that exit, the easier it is to reconstruct the action list.

## Homework (Code)
1. Write a program that calls `fork()`. Before calling `fork()` , have the main process access a variable (e.g., `x`) and set its value to something (e.g., 100). What value is the variable in the child process?What happens to the variable when both the child and parent change the value of x?

I explore this in p1. Seems like the variables are not shared globally, and setting the value of x in a child process doesn't affect the value of x in the parent process.

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/05-processes-api (master)$ ./p1.out
parent - pid:4173, x:0
before setting parent - pid:4173, x:0
after setting parent - pid:4173, x:3
pid:4173, x:3
before setting child - pid:4174, x:0
after setting child - pid:4174, x:1
pid:4174, x:1
```

2. Write a program that opens a file (with the `open() `system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

Yeah, they can both access it, and they seem to have no problem writing concurrently, although I wonder what would happen if I needed to write more. Conceptually, an operating system would need to be able to handle two users simultaneously writing to a file at the same time. Since the file descriptor is a pointer, a child process closing it doesn't affect the parent process.

3. Write another program using `fork()`. The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

You can make sure the child process executes before the parent with a call to `sleep()` in the parent process, but that seems imprecise to me -- imagine the child process runs longer than your call to sleep, or drastically shorter. Calling wait guarantees the parent process executes as soon as the child process is complete.

4. Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`.  Why do you think there are so many variants of the same basic call?

There are several exec calls because requirements for exec have changed. There are differences in how the program is found, how arguments are specified, and where the environment variables come from. I wonder if I need to fork the process in order to call exec, or if I can't just call it in the parent process? [This](https://stackoverflow.com/questions/1653340/differences-between-fork-and-exec) is a pretty good SO on it.

5. Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

The wait result code is the pid of the child process. What happens when you have multiple forks, what is the result code? Seems like if you do that, there are multiple calls to wait, and one fails. Not sure what is happening -- need to instrument more to investigate. As for putting wait() in the child, you get a result code that is -1, and it ignores the call.

6. Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

The waitpid() call would allow you to wait on any arbitrary process completing before the parent process resumes. From the [wait man page](https://linux.die.net/man/3/waitpid):

The waitpid() function is provided for three reasons:
  1. To support job control
  2. To permit a non-blocking version of the wait() function
  3. To permit a library routine, such as system() or pclose(), to wait for its children without interfering with other terminated children for which the process has not waited

7. Write a program that creates a child process, and then in the child closes standard output (`STDOUT_FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

No output is emitted to the terminal. According to the [print man page](https://man7.org/linux/man-pages/man3/printf.3.html), printf prints to stdout, so it has nowhere else to go.

8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

I'm not really sure what's going on with pipe here. Seems like you need to call it before you fork (of course!). Let me see if I can talk through what I see in p8. Might be a good chance to run a debugger and check the values in pipefd before and after pipe() is called, and see if these correspond to process ids (pid).
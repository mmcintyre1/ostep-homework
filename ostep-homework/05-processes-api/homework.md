[GitHub README on fork.py](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-api/README-fork.md)

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

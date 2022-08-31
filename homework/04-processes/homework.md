[GitHub README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-intro/README.md)

1. Run `process-run.py` with the following flags:`-l 5:100,5:100`. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the `-c` and `-p `flags to see if you were right.

The CPU usage should be 100%. The first process should run 5 instructions while the second process waits, then the second process runs its 5 instructions after the first process completes.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 5:100,5:100 -c -p
    Time        PID: 0        PID: 1           CPU           IOs
    1        RUN:cpu         READY             1
    2        RUN:cpu         READY             1
    3        RUN:cpu         READY             1
    4        RUN:cpu         READY             1
    5        RUN:cpu         READY             1
    6           DONE       RUN:cpu             1
    7           DONE       RUN:cpu             1
    8           DONE       RUN:cpu             1
    9           DONE       RUN:cpu             1
    10           DONE       RUN:cpu             1

    Stats: Total Time 10
    Stats: CPU Busy 10 (100.00%)
    Stats: IO Busy  0 (0.00%)
    ```

2. Now run with these flags:./process-run.py `-l 4:100,1:0`. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use `-c` and `-p` to find out if you were right.

    I would think here that it takes 4 clock cycles, since the second process can complete its IO without using (blocking the CPU).

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 4:100,1:0 -p -c
    Time        PID: 0        PID: 1           CPU           IOs
    1        RUN:cpu         READY             1
    2        RUN:cpu         READY             1
    3        RUN:cpu         READY             1
    4        RUN:cpu         READY             1
    5           DONE        RUN:io             1
    6           DONE       WAITING                           1
    7           DONE       WAITING                           1
    8           DONE       WAITING                           1
    9           DONE       WAITING                           1
    10           DONE       WAITING                           1
    11*          DONE   RUN:io_done             1

    Stats: Total Time 11
    Stats: CPU Busy 6 (54.55%)
    Stats: IO Busy  5 (45.45%)
    ```

    That's not what I expected. I think I understand why. IO_LENGTH defaults to 5, so an IO takes at least that many. And it looks like the CPU is needed to initiate an IO request, meaning process 2 can't start until cycle 5. Then there is an additional cycle needed to report the finished IO, meaning the total is 11.

3. Switch the order of the processes: `-l 1:0,4:100`. What happens now? Does switching the order matter? Why? (As always, use `-c` and `-p` to see if you were right)

    An IO gets issued on cycle 1, then process 2 can start at cycle 2 and it will complete in cycle 5, then cycle 6 should report the IO is complete.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 1:0,4:100 -p -c
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1
    2        WAITING       RUN:cpu             1             1
    3        WAITING       RUN:cpu             1             1
    4        WAITING       RUN:cpu             1             1
    5        WAITING       RUN:cpu             1             1
    6        WAITING          DONE                           1
    7*   RUN:io_done          DONE             1

    Stats: Total Time 7
    Stats: CPU Busy 6 (85.71%)
    Stats: IO Busy  5 (71.43%)
    ```

    Weird on what happened with cycle 6. Why wasn't anything running? Same thing as the IO, needs to report 'DONE' or needs a single cycle to context switch?

4. We’ll now explore some of the other flags. One important flag is `-S`, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH_ON_END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (`-l 1:0,4:100 -c -S SWITCH_ON_END`), one doing I/O and the other doing CPU work?

    It will run in the same time as with arguments `-l 4:100,1:0`. IO will run until 6, finish in 7, and process 2 will start in cycle 8 and run until cycle 11.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 1:0,4:100 -c -S SWITCH_ON_END -p -c
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1
    2        WAITING         READY                           1
    3        WAITING         READY                           1
    4        WAITING         READY                           1
    5        WAITING         READY                           1
    6        WAITING         READY                           1
    7*   RUN:io_done         READY             1
    8           DONE       RUN:cpu             1
    9           DONE       RUN:cpu             1
    10           DONE       RUN:cpu             1
    11           DONE       RUN:cpu             1

    Stats: Total Time 11
    Stats: CPU Busy 6 (54.55%)
    Stats: IO Busy  5 (45.45%)
    ```

5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (`-l 1:0,4:100 -c -S SWITCH_ON_IO`). What happens now? Use `-c` and `-p` to confirm that you are right.

    We should see the same as running `-l 1:0,4:100`, since `SWITCH_ON_IO` is default behavior.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 1:0,4:100 -c -S SWITCH_ON_IO -p
    Time        PID: 0        PID: 1           CPU           IOs
    1         RUN:io         READY             1
    2        WAITING       RUN:cpu             1             1
    3        WAITING       RUN:cpu             1             1
    4        WAITING       RUN:cpu             1             1
    5        WAITING       RUN:cpu             1             1
    6        WAITING          DONE                           1
    7*   RUN:io_done          DONE             1

    Stats: Total Time 7
    Stats: CPU Busy 6 (85.71%)
    Stats: IO Busy  5 (71.43%)
    ```

6. One other important behavior is what to do when an I/O completes. With `-I IO_RUN_LATER`, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run `./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p`) Are system resources being effectively utilized?

    Should run the first IO instruction, then switch to second process, then after that is complete run the second IO, then the third process, then the third IO, then the fourth process. Should complete in cycle 21.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
    Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1
    2        WAITING       RUN:cpu         READY         READY             1             1
    3        WAITING       RUN:cpu         READY         READY             1             1
    4        WAITING       RUN:cpu         READY         READY             1             1
    5        WAITING       RUN:cpu         READY         READY             1             1
    6        WAITING       RUN:cpu         READY         READY             1             1
    7*         READY          DONE       RUN:cpu         READY             1
    8          READY          DONE       RUN:cpu         READY             1
    9          READY          DONE       RUN:cpu         READY             1
    10          READY          DONE       RUN:cpu         READY             1
    11          READY          DONE       RUN:cpu         READY             1
    12          READY          DONE          DONE       RUN:cpu             1
    13          READY          DONE          DONE       RUN:cpu             1
    14          READY          DONE          DONE       RUN:cpu             1
    15          READY          DONE          DONE       RUN:cpu             1
    16          READY          DONE          DONE       RUN:cpu             1
    17    RUN:io_done          DONE          DONE          DONE             1
    18         RUN:io          DONE          DONE          DONE             1
    19        WAITING          DONE          DONE          DONE                           1
    20        WAITING          DONE          DONE          DONE                           1
    21        WAITING          DONE          DONE          DONE                           1
    22        WAITING          DONE          DONE          DONE                           1
    23        WAITING          DONE          DONE          DONE                           1
    24*   RUN:io_done          DONE          DONE          DONE             1
    25         RUN:io          DONE          DONE          DONE             1
    26        WAITING          DONE          DONE          DONE                           1
    27        WAITING          DONE          DONE          DONE                           1
    28        WAITING          DONE          DONE          DONE                           1
    29        WAITING          DONE          DONE          DONE                           1
    30        WAITING          DONE          DONE          DONE                           1
    31*   RUN:io_done          DONE          DONE          DONE             1

    Stats: Total Time 31
    Stats: CPU Busy 21 (67.74%)
    Stats: IO Busy  15 (48.39%)
    ```

    Never switches back to IO, so not the most efficient usage of resources. The method I outlined above would be more efficient.

7. Now run the same processes, but with -I IO_RUN_IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?

    This should exhibit the behavior outlined above and complete on cycle 21. Jumping back to execute a longer running but non-blocking instruction is useful.

    ```console
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/04-processes $ python3 process_run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
    Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
    1         RUN:io         READY         READY         READY             1
    2        WAITING       RUN:cpu         READY         READY             1             1
    3        WAITING       RUN:cpu         READY         READY             1             1
    4        WAITING       RUN:cpu         READY         READY             1             1
    5        WAITING       RUN:cpu         READY         READY             1             1
    6        WAITING       RUN:cpu         READY         READY             1             1
    7*   RUN:io_done          DONE         READY         READY             1
    8         RUN:io          DONE         READY         READY             1
    9        WAITING          DONE       RUN:cpu         READY             1             1
    10        WAITING          DONE       RUN:cpu         READY             1             1
    11        WAITING          DONE       RUN:cpu         READY             1             1
    12        WAITING          DONE       RUN:cpu         READY             1             1
    13        WAITING          DONE       RUN:cpu         READY             1             1
    14*   RUN:io_done          DONE          DONE         READY             1
    15         RUN:io          DONE          DONE         READY             1
    16        WAITING          DONE          DONE       RUN:cpu             1             1
    17        WAITING          DONE          DONE       RUN:cpu             1             1
    18        WAITING          DONE          DONE       RUN:cpu             1             1
    19        WAITING          DONE          DONE       RUN:cpu             1             1
    20        WAITING          DONE          DONE       RUN:cpu             1             1
    21*   RUN:io_done          DONE          DONE          DONE             1

    Stats: Total Time 21
    Stats: CPU Busy 21 (100.00%)
    Stats: IO Busy  15 (71.43%)
    ```

8. Now run with some randomly generated processes: `-s 1 -l 3:50,3:50` or `-s 2 -l 3:50,3:50` or `-s 3 -l 3:50,3:50`. See if you can predict how the trace will turn out. What happens when you use the flag `-I IO_RUN_IMMEDIATE` vs. `-I IO_RUN_LATER`? What happens when you use `-S SWITCH_ON_IO` vs. `-S SWITCH_ON_END`?

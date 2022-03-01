[mlfq README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-sched-mlfq/README.md)

## Homework Questions
1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

These execution stacks are pretty long, but after answering the following questions it's much clearer what is going to happen.

2. How would you run the scheduler to reproduce each of the examples in the chapter?

8.4 - `python3 mlfq.py -l 0,125,0:50,75,1 -c -i 1 -S`
8.5 Left - `python3 mlfq.py -l 0,150,0:100,50,1:100,50,1 -c -i 1 -S`
8.5 Right - `python3 mlfq.py -l 0,130,0:100,15,1:100,15,1 -c -i 1 -S -B 50` (need to play with this one a little)
8.6 Left - `python3 mlfq.py -l 0,50,5:0,50,0 -S -i 1 -c`
8.6 Right - `python3 mlfq.py -l 0,50,5:0,50,0 -i 1 -c` - removed the `-S` imperative
8.7 - `python3 mlfq.py -l 0,150,0:0,150,0 -Q 10,25,50 -c`

3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?

If you don't have an I/O, then each job will run for the quanta length and then cede to the next job. Or you could have all jobs issue I/O at the same cadence. Is it just having all jobs be the exact same? How does round robin behave when there is I/O? job 0 issues a blocking I/O, so job 1 takes over. After job 1 runs for its quanta, it returns to job 0? Or when job 0 completes its I/O does it take back control? Will it look like fig 8.6?

4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the `-S` flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

It'd look something like this: `python3 mlfq.py -l 0,50,5:0,50,0 -S -i 1 -c`

5. Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the `-B` flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?

6. One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the `-I` flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.
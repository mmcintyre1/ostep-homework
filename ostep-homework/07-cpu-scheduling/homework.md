[Scheduler README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-sched/README.md)

## Homework Questions
1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

Things should be identical with SJF and FIFO since jobs are equal length.
1: tt -> 200, r -> 0
2: tt -> 400, r -> 200
3: tt -> 600, r -> 400

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/07-cpu-scheduling (master)$ python3 scheduler.py -p SJF -l 200,200,200 -c
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

2. Now do the same but with jobs of different lengths: 100, 200, and 300.

SJF:
1: tt -> 100, r -> 0
2: tt -> 300, r -> 100
3: tt -> 600, r -> 300
avg: tt -> 333.33, r -> 133.33

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/07-cpu-scheduling (master)$ python3 scheduler.py -p SJF -l 100,200,300 -c
ARG policy SJF
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

For FIFO, it depends on the order the jobs execute in. Looking at `scheduler.py`, they are just processed in the order they are received, so things will again look identical to SJF.

3. Now do the same, but also with the RR scheduler and a timeslice of 1.

Response is going to improve drastically, but turnaround time should also increase for all three, and not just for

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/07-cpu-scheduling (master)$ python3 scheduler.py -p RR -l 100,200,300 -c
ARG policy RR
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **
[...]

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 298.00  Wait 198.00
  Job   1 -- Response: 1.00  Turnaround 499.00  Wait 299.00
  Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00
```

4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

Workloads where all jobs are the same length, or workloads where the jobs already arrive in the order of their length, as we saw in question 2.

5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

It will deliver the same response times if the quantum length is the same as job length. If you have jobs that are longer than the quantum length, using SJF will result in longer response times because there is no mechanism to switch to different job until the shortest job is complete. If you have some preempting mechanism, there might be a scenario where new jobs that come in are each shorter than currently executing jobs, and if this matches up to the current quantum for RR, they could potentially be the same response time (or faster), but this is coincidence.

6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

Response times increase as job lengths increase, unless there is a preempting mechanism.

```console
mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/ostep-homework/07-cpu-scheduling (master)$ python3 scheduler.py -p SJF -l 100,200,300,400,500,600,700 -c
ARG policy SJF
ARG jlist 100,200,300,400,500,600,700

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
  Job 3 ( length = 400.0 )
  Job 4 ( length = 500.0 )
  Job 5 ( length = 600.0 )
  Job 6 ( length = 700.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )
  [ time 600 ] Run job 3 for 400.00 secs ( DONE at 1000.00 )
  [ time 1000 ] Run job 4 for 500.00 secs ( DONE at 1500.00 )
  [ time 1500 ] Run job 5 for 600.00 secs ( DONE at 2100.00 )
  [ time 2100 ] Run job 6 for 700.00 secs ( DONE at 2800.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00
  Job   3 -- Response: 600.00  Turnaround 1000.00  Wait 600.00
  Job   4 -- Response: 1000.00  Turnaround 1500.00  Wait 1000.00
  Job   5 -- Response: 1500.00  Turnaround 2100.00  Wait 1500.00
  Job   6 -- Response: 2100.00  Turnaround 2800.00  Wait 2100.00

  Average -- Response: 800.00  Turnaround 1200.00  Wait 800.00
```

7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

As quantum lengths increase, response time increases as well. The worst case for response time would be longer than the longest running job. If the only input we have is amount of jobs and not their length, it's harder to write an equation I'd think.
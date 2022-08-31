# 7 - Scheduling
- scheduling is higher level policy for _when_ to apply lower level mechanism (e.g., context switching) when virtualizing resources
- in order to compare different scheduling policies, need metrics to compare

## Key Metrics
**turnaround time**
  - time in which a job completes minus the time a job arrives
  - $ T_{turnaround} = T_{completion} - T_{arrival} $

**fairness**
  - the equality with which jobs are treated
  - one example is Jain's Fairness Index
  - often at odds with performance, as most fair way to run jobs isn't often the most performant

**response time**
  - time when a job arrives to when it's first scheduled
  - optimizations for turnaround time might not be helpful for response time
  - $ T_{response} = T_{firstrun} - T_{arrival} $

**overlap**
  - when dealing with I/O (or any blocking task), it is good to kick off the blocking task then switch, or to overlap executions

## First In, First Out (FIFO)
- simplest algo for scheduling -- job that arrives is first to be processed
- suffers from **convoy effect** -- large, expensive job blocks small, fast jobs
- normally only works when all jobs run in same amount of time

## Shortest Job First (SJF)
- jobs are organized based on job length at arrival
- optimal if all jobs arrive at the same time, but bad for response time
- if not all jobs arrive at same time, you need to add **preemption** (like an interrupt for new arrivals), called **Shortest Time-to-Completion First** (STCF)
- most modern schedulers are preemptive

## Shortest Time-to-Completion First (STCF)
- adds preemption to shortest job first scheduling
- any time a new job enters the system, the scheduler determines which job has least time left and schedules that one
-

## Round Robin
- aka _time slicing_
- instead of running job to completion, jobs are run for a _time slice_ (aka scheduling quantum)
- need to _amortize_ cost (spread cost out over long term) of context switching, so you don't want to switch context too often or wait too long so as to remove all benefits of round robin algo
- round robin is more fair and like any policy that is fair will perform more poorly on turnaround time -- can run shorter jobs to completion if you are willing to be unfair, which might affect response time
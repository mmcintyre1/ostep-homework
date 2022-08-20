# Homework
[malloc.py README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-freespace/README.md)

1. First run with the flags `-n 10 -H 0 -p BEST -s 0` to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?

    ```sh
    seed 0
    size 100
    baseAddr 1000
    headerSize 0
    alignment -1
    policy BEST
    listOrder ADDRSORT
    coalesce False
    numOps 10
    range 10
    percentAlloc 50
    allocList
    compute False

    ptr[0] = Alloc(3) returned 1004
    List [addr: 1003, size:97]

    Free(ptr[0])
    returned 0
    List [(1000,3), (1003,97)]

    ptr[1] = Alloc(5) returned 1003
    List [(1000, 3), (1008, 92)]

    Free(ptr[1])
    returned 0
    List [(1000, 3), (1003, 5), (1008, 92)]

    ptr[2] = Alloc(8) returned 1008
    List [(1000, 3), (1003, 5), (1016, 84)]

    Free(ptr[2])
    returned 0
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 84)]

    ptr[3] = Alloc(8) returned 1008
    List [(1000, 3), (1003, 5), (1016, 84)]

    Free(ptr[3])
    returned 0
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 84)]

    ptr[4] = Alloc(2) returned 1002
    List [(1002, 1), (1003, 5), (1008, 8), (1016, 84)]

    ptr[5] = Alloc(7) returned 1008
    List [(1002, 1), (1003, 5), (1015, 1), (1016, 84)]
    ```

2. How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?

    Last four operations change
    ```sh
    Free(ptr[2])
    returned 0
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 84)]

    ptr[3] = Alloc(8) returned 1016
    List [(1000, 3), (1003, 5), (1008, 8), (1024, 76)]

    Free(ptr[3])
    returned 0
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 8), (1024, 76)]

    ptr[4] = Alloc(2) returned 1024
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 8), (1026, 74)]

    ptr[5] = Alloc(7) returned 1026
    List [(1000, 3), (1003, 5), (1008, 8), (1016, 8), (1033, 67)]
    ```

3. What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?

    Looks the same as BEST fit, but there is less list traversal.

4. For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact.

    tough to get WORST fit to work well with any policy. The free list was long and all the elements always needed to be searched. Same is true for BEST, but the free list wasn't too fragmented. FIRST and SIZESORT- led to quick traversal. With coalescing it might be a good approach.

5. Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?

    When using SIZESORT(+|-) and INSERT-FRONT and INSERT-BACK, the free list was still really large at the end, and there was tons of traversal for all the policies. The only one where coalescing really helped was ADDRSORT.

6. What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?

    Closer to 100%, you can't allocate any new memory, and closer to 0%, you don't really move beyond the first bit of your address space.

7. What kind of specific requests can you make to generate a highly-fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.

    Picking policies and sorting so you aren't freeing potentially contiguous space is a good way to have highly fragmented address space. If you want a really large free list, you'd want to pick the policies and sorting that gives you new space that is 1 or 2 offset from what is available.

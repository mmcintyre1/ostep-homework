## Homework Questions
1. First, write a simple program called `null.c` that creates a pointer to an integer, sets it to `NULL`, and then tries to de-reference it. Compile this into an executable called null. What happens when you run this program?

- Segmentation Fault

2. Next, compile this program with symbol information included (with the `-g` flag).  Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing `gdb null` and then, once `gdb` is running, typing run. What does gdb show you?

```shell
(gdb) run
Starting program: /home/mike/projects/ostep-homework/homework/14-memory-api/null.out

Program received signal SIGSEGV, Segmentation fault.
0x0000000000401170 in main (argc=1, argv=0x7fffffffda88) at null.c:7
7         printf("%d\n", *x);
```

3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens.  Run this by typing in the following: `valgrind --leak-check=yes null`. What happens when you run this? Can you interpret the output from the tool?

```shell
==519== HEAP SUMMARY:
==519==     in use at exit: 4 bytes in 1 blocks
==519==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==519==
==519== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==519==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==519==    by 0x40115F: main (null.c:5)
==519==
==519== LEAK SUMMARY:
==519==    definitely lost: 4 bytes in 1 blocks
==519==    indirectly lost: 0 bytes in 0 blocks
==519==      possibly lost: 0 bytes in 0 blocks
==519==    still reachable: 0 bytes in 0 blocks
==519==         suppressed: 0 bytes in 0 blocks
```

4 bytes in 1 blocks means I've lost 4 bytes of memory without reclaiming/deleting them.

4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use `gdb` to find any problems with it? How about valgrind(again with the `--leak-check=yes` flag)?

- Program runs fine, nothing shows up on `gdb`, but you can see the leak with valgrind.

5. Write a program that creates an array of integers called `data` of size 100 using `malloc`; then, set `data[100]` to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?

- Nothing happens when you run it, although valgrind gives an invalid write of size 4.

```shell
==1854== Invalid write of size 4
==1854==    at 0x401168: main (data_array.c:5)
==1854==  Address 0x4a4a1d0 is 224 bytes inside an unallocated block of size 4,194,032 in arena "client"
==1854==
==1854==
==1854== HEAP SUMMARY:
==1854==     in use at exit: 0 bytes in 0 blocks
==1854==   total heap usage: 1 allocs, 1 frees, 100 bytes allocated
==1854==
==1854== All heap blocks were freed -- no leaks are possible
```

6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?

- Things run with no problem, and it prints the value I would expect. Not sure why this happens -- would've thought freeing the memory would remove the value. valgrind shows an invalid read though.

```shell
==2359== Invalid read of size 4
==2359==    at 0x401192: main (print_release.c:7)
==2359==  Address 0x4a4a1d0 is 224 bytes inside an unallocated block of size 4,194,032 in arena "client"
```

7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

- gives me an invalid pointer. I don't see much in `gdb` or `valgrind`. Assuming that invalid pointers are typically raised on releasing memory, might be helpful to set breakpoints and walk through the code.


8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use `realloc()` to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use `realloc()` to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use `valgrind` to help you find bugs.

9.  Spend more time and read about using `gdb` and `valgrind`. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.
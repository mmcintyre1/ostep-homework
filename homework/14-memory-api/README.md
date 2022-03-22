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

3. Finally, use the valgrind tool on this program. We’ll use the memchecktool that is a part of valgrindto analyze what happens.  Run this by typing in the following: `valgrind --leak-check=yes null`. What happens when you run this? Can you interpret the output from the tool?

4. Write a simple program that allocates memory usingmalloc()butforgets to free it before exiting. What happens when this programruns? Can you usegdbto find any problems with it? How aboutvalgrind(again with the--leak-check=yesflag)?

5. Write a program that creates an array of integers calleddataof size100 usingmalloc; then, setdata[100]to zero. What happenswhen you run this program? What happens when you run thisprogram usingvalgrind? Is the program correct?

6. Create a program that allocates an array of integers (as above), freesthem, and then tries to print the value of one of the elements ofthe array. Does the program run? What happens when you usevalgrindon it?

7. Now pass a funny value to free (e.g., a pointer in the middle of thearray you allocated above). What happens? Do you need tools tofind this type of problem?

8. Try out some of the other interfaces to memory allocation. For ex-ample, create a simple vector-like data structure and related rou-tines that userealloc()to manage the vector. Use an array tostore the vectors elements; when a user adds an entry to the vec-tor, userealloc()to allocate more space for it. How well doessuch a vector perform? How does it compare to a linked list? Usevalgrindto help you find bugs.

9.  Spend more time and read about usinggdbandvalgrind. Know-ing your tools is critical; spend the time and learn how to becomean expert debugger in the UNIXand C environment.
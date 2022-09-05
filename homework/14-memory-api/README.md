# 14 - Memory API

## Types of Memory
### stack
- allocations and deallocations of stack memory are handled _implicitly_ by the compiler
- sometimes called automatic memory for this reason
- when you return from function, the compiler deallocates this memory, so if you need data to survive the invocation of a function, don't leave it on the stack

```c
void func() {
    int x; // declares an integer on the stack
...
}
```

### heap
- more long-lived memory
- allocations and deallocations are handled _explicitly_ by the programmer

```c
void func() {
    int *x = (int *) malloc(sizeof(int));
...
}
```

## malloc()
- you pass the function a size of some room on the heap, it either succeeds and gives you a pointer to the newly-allocated space or fails and returns `NULL`
- pass in `size_t` which describes how many bytes you need
- `NULL` in C is just a macro for 0
- need to include header file `stdlib.h`

`double *d = (double *) malloc(sizeof(double));`

- using `sizeof()` is a compile-time operator and not a run-time function and is considered best practice because size of various primitives change on a per-system basis (most systems `int` is 4 bytes and `double` is 8, but not all)
- for strings, use `malloc(strlen(s) + 1)`, the + 1 for an end-of-string character

## free()
- takes one argument, a pointer returned by malloc
- size of allocated region is tracked by the memory-allocation library itself

## Common Memory Errors
- many new languages are **garbage collected**, meaning there is a process to reclaim/free memory that is no longer in use -- this is an example of **automatic memory management**
- **segmentation fault** - an error raised when you manage memory wrong
- **forgetting to allocate memory** - if you don't allocate, you'll run into a segfault and the process will die, even if the program compiled correctly
- **not allocating enough memory** - often called a _buffer overflow_; sometimes this won't break a program but will cause some data to be unexpectedly overwritten
- **forgetting to initialize allocated memory** - this will cause an **uninitialized read** where a program will read some unknown data from the heap
- **forgetting to free memory** - also known as a memory leak, and affects GC languages too
- **freeing memory before you are done with it** - aka a **dangling pointer** and can cause overwritten memory or a program crash
- **freeing memory repeatedly** - aka a **double free** and the effects are undefined but often results in crashes
- **calling free() incorrectly** - aka an **invalid free** and occurs when you pass free an unexpected value

- **purify** and **valgrind** are good tools for finding memory-related problems
- **break** - the location of the end of the heap for a program and is changed via the system call `sbrk` or `brk`, but should never be done manually
- `calloc()` allocates memory and zeroes it before returning
- `realloc()` is useful when you've allocated space (e.g., for an array) and need to add something to it

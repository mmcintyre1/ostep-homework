# 17 - Free Space Management
- managing space is easier if the space is divided into fixed-size units
- much harder when sizes are variable, such as user-level memory-allocation libraries like `malloc`
- problems are with **external fragmentation**
- `sbrk` system call grows heap

## Low-Level Mechanisms
- **splitting** - memory allocator will find a free chunk of memory that can satisfy request and split in two
- **coalescing** - when memory is freed, the memory allocator looks at adjacent chunks to see if freed space can be merged to an existing chunk

- `free()` doesn't take a `size` parameter, so a **header** block is used to track that extra information
- **header** takes up a small amount of space on its own
  - when a user requests *N* bytes of memory, the memory library searches for a free chunk of *N* bytes plus the header

```c
typedef struct {
  int size;
  int magic; // for integrity checking
} header_t;
```

- a free list is created within the free space itself

[free-space.png](free-space.png)

- if you need to grow the heap, one option is to just fail and return NULL
- most traditional allocators start with a small heap and grow via `sbrk` in most UNIX systems

## Basic Strategies
- ideal memory allocation strategy is fast and minimizes fragmentation

### Best Fit
- search through free list and find chunks that are as big or bigger than request, and return smallest of those
- downsides are that you need to search the whole list

### Worst Fit
- search through free list and find the largest chunk and break off the requested amount
- downsides are that you need to search the whole list, and most studies show it performs poorly and leads to excess fragmentation

### First Fit
- search through free list and find the first block that is big enough
- fast, but can pollute the beginning of the free list with small objects
- **address-based ordering** helps keep the beginning of the list clear by ordering the free list by address of free space
  - coalescing is easier and fragmentation is reduced

### Next Fit
- keep an extra pointer to last location searched
- searches through free space are more uniform
- similar performance to first fit

[example-memory.png](example-memory.png)

if searching for 15 bytes
- best fit picks 20
- worst picks 30
- first fit picks 30

### Segregated Lists
- if application has popular-sized requests, keep a separate list to manage objects of that size
- an example is **slab allocator**
  - allocates object caches for kernel objects that are likely to be requested ferquently (e.g., locks, file-system inodes, etc)
  - when cache is running low, it asks for some slabs of memory from a general allocator
  - freed memory will go back to general memory
  - objects are kept in a pre-initialized state, as initialization and destruction of data structures is costly

### Buddy Allocation
- memory is one big space, and when memory is requested, space is divided by two until a suitable block is found
- key is that when memory is freed, allocator will check its buddies to see if it can be coalesced all the way up the tree

[buddy-heap.png](buddy-heap.png)

- most of these approaches have difficulty scaling, as searching can be quite slow
- glibc allocator is an example of a C allocator in real use
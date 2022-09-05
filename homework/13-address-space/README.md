# 13 - The Abstraction: Address Spaces
- in the early days, machines didn't provide a memory abstraction -- one process ran at a time and used all the memory
- soon, people began to share machines thus beginning **multiprogramming**, where multiple processes were ready to run at any time and the OS would switch between them
- later, many people wanted to **time share** machines

## Address Space
- an easy to use abstraction of physical memory
- the address space of a program contains all of the memory state of a running program
- **stack** - stores where a process is in its function call chain, local variables, and for parameters and return values to and from routines
- **heap** - used for dynamically-allocated, user-managed memory (e.g., `malloc()` or `new`)
- stack and heap are placed at opposite ends of the address space to allow for negative and positive growth, although this is just a convention

![address space](address-space.png)

- **virtual addresses** - in virtualizing the memory, a process never has a physical address, just the virtual -- every address you see is virtual

### Goals of the Address Space
- **transparency** - OS should implement virtual memory in a way that is invisible to the running program
- **efficiency** - OS should make the virtualization efficient in time (not making programs run much more slowly) and space (not using too much memory for structures needed to support virtualization)
- **protection** - OS should make sure to protect processes from one another as well as the OS -- only a process should be allowed to change what it has stored in memory; important to delivery concept of **isolation**

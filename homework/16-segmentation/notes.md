# Segmentation
- approach of using base and bounds is wasteful
- how can we support a large address space with free space between heap and stack?
- we can have base and bounds pair per logical **segment** of address space
- **segment** is a contiguous portion of address space of a particular length
- **sparse address spaces** - large amounts of unused address space in a large address space
- **segmentation fault** - violation from memory access on a segmented machine to an illegal address

two approaches for hardware to determine which segment an address is in
1. **explicit**
    - chop up address space into segments based on top few bits of virtual address
    - first two bits are segment, remaining are offset into segment
    - using two bits leaves one segment unused (00, 01, 10, 11 <- unused), so some systems put code in same section as heap and only use one bit to select
    [offset.png](offset.png)
2. **implicit**
    - hardware determines how the address was formed, e.g., addresses from program counter (instruction fetch) then address is within code segment

- hardware also needs to know which way segment grows to accommodate stack in addition to base and bounds registers
- to save memory, sometimes its useful to share memory segments between address spaces
  - need protection bits to to indicate read or write permissions
[registers.png](registers.png)

**fine-grained segementation** - many smaller segments, but requires a segment table as a map
**course-grained segmentation** - only a few segments, i.e., code, stack, heap
- fine-grained segmentation gives more flexibility for more use cases

- **external fragmentation** - physical memory becomes full of little holes of free space, making it difficult to allocate or grow segments
- **compact physical memory** - rearrange existing segments to ease fragmentation
- **compaction** is expensive and copying segments is memory-intensive and uses a fair amount of processor time
- **free list management algorithm** - keep large extents of memory available for allocation
- other algorithms like best-fit, worst-fit, first-fit, buddy algorithm

-

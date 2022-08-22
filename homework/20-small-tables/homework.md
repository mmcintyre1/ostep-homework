# Homework

[pmt README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-smalltables/README.md)

1. With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. How many registers do you need to locate a two-level page table? A three-level table?

    There's a single register, the page directory base register (PDBR) that points to the level-0 page directory, which contains pointers to the page table below.

2. Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. How many memory references are needed to perform each lookup?

    page size = 32 bytes -> offset 5 (2**5 = 32)
    virtual address space = 32 kb -> 15, VPN = 10 (15 - 10)
    128 pages, offset 5, PFN 7 (2**7 = 128)

    611c
    011000 (pde index) 01000 (pt index) 11100 (offset)
    Start at page table 108 - index at 011000 (24) = 0xa1
    0xa1 in binary = 10100001. first bit is 1, so valid, remaining 0100001 (33)
    go to page 33, look at index 01000 (8) = 0xb5
    0xb5 in binary = 10110101. first bit is 1, so valid, remaining 0110101 (53)
    concat 0110101 and offset 11100 = 011010111100 = 0x6bc

    3da8
    001111 01101 01000
    page 108, index at 001111 (15) = d6 (11010110)
    1 - valid, 1010110 (86)
    page 86, index at 01101 (13) = 7f (01111111)
    0 - invalid 1111111
    FAULT

3. Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? Will they lead to lots of cache hits (and thus fast accesses?) Or lots of misses (and thus slow accesses)?
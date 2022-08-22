# Homework

[pmt README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-smalltables/README.md)

1. With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. How many registers do you need to locate a two-level page table? A three-level table?

    There's a single register, the page directory base register (PDBR) that points to the level-0 page directory, which contains pointers to the page table below.

2. Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. How many memory references are needed to perform each lookup?

    page size = 32 bytes -> offset 5 (2**5 = 32)
    virtual address space = 32 kb -> 15, VPN = 10 (15 - 10)
    128 pages, offset 5, PFN 7 (2**7 = 128)

    Virtual Address 611c: Translates To What Physical Address (And Fetches what Value)? Or Fault? 01100 00100011100
    Virtual Address 3da8: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 17f5: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 7f6c: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 0bad: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 6d60: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 2a5b: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 4c5e: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 2592: Translates To What Physical Address (And Fetches what Value)? Or Fault?
    Virtual Address 3e99: Translates To What Physical Address (And Fetches what Value)? Or Fault?
3. Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? Will they lead to lots of cache hits (and thus fast accesses?) Or lots of misses (and thus slow accesses)?
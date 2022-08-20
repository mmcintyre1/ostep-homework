# Homework

[plt README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-paging/README.md)

1. 1. Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the `-v` flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with
these flags:

`-P 1k -a 1m -p 512m -v -n 0`
`-P 1k -a 2m -p 512m -v -n 0`
`-P 1k -a 4m -p 512m -v -n 0`

Then, to understand how linear page table size changes as page size grows:

`-P 1k -a 1m -p 512m -v -n 0`
`-P 2k -a 1m -p 512m -v -n 0`
`-P 4k -a 1m -p 512m -v -n 0`

Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows?

    So as address space gets larger, if page size stays the same you'll need more pages to hold all the address space, and the inverse is also true, meaning that as page size gets larger and address space stays the same, you'll need less pages. If page table entries are accessed by index, does size really matter? And how does page size affect anything? Are more pages bad or good? Seems like more is additional overhead in page table entries.

2. Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the `-u` flag. For example:

`-P 1k -a 16k -p 32k -v -u 0`
`-P 1k -a 16k -p 32k -v -u 25`
`-P 1k -a 16k -p 32k -v -u 50`
`-P 1k -a 16k -p 32k -v -u 75`
`-P 1k -a 16k -p 32k -v -u 100`

    ```sh
    ARG seed 0
    ARG address space size 16k
    ARG phys mem size 32k
    ARG page size 1k
    ARG verbose True
    ARG addresses -1


    The format of the page table is simple:
    The high-order (left-most) bit is the VALID bit.
    If the bit is 1, the rest of the entry is the PFN.
    If the bit is 0, the page is not valid.
    Use verbose mode (-v) if you want to print the VPN # by
    each entry of the page table.

    Page Table (from entry 0 down to the max size)
    [       0]  0x80000018
    [       1]  0x00000000
    [       2]  0x00000000
    [       3]  0x8000000c
    [       4]  0x80000009
    [       5]  0x00000000
    [       6]  0x8000001d
    [       7]  0x80000013
    [       8]  0x00000000
    [       9]  0x8000001f
    [      10]  0x8000001c
    [      11]  0x00000000
    [      12]  0x8000000f
    [      13]  0x00000000
    [      14]  0x00000000
    [      15]  0x80000008

    Virtual Address Trace
    VA 0x00003385 (decimal:    13189) --> PA or invalid address?
    VA 0x0000231d (decimal:     8989) --> PA or invalid address?
    VA 0x000000e6 (decimal:      230) --> PA or invalid address?
    VA 0x00002e0f (decimal:    11791) --> PA or invalid address?
    VA 0x00001986 (decimal:     6534) --> PA or invalid address?
    ```

    Steps:
    i. take address space, get power of 2 (16kb, 2^14 = 16384)
    ii. use page size to identify offset (1k, 2^10 = 1024)
    iii. subtract one from the other -- first four numbers are the virtual page number
    iv. if first bit after 0x is 1, then it's a valid address
    v. take the page table physical frame number, and shift bits left the amount of the offset
    vi. do a bitwise OR between the physical frame number and your offset to get physical memory location

    e.g. 0x1986
    0110 01 1000 0110
    VPN = 0110 (b), 6 (d)
    PFM = 0x1d << 10 -> 111010000000000
    physical address = 111010000000000 OR 01 1000 0110 = 111010110000110, 30086, 0x7586


What happens as you increase the percentage of pages that are allocated in each address space?

    As you increase pages allocated to address space, you have fewer invalid accesses.

3. Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety:

`-P 8 -a 32 -p 1024 -v -s 1`
`-P 8k -a 32k -p 1m -v -s 2`
`-P 1m -a 256m -p 512m -v -s 3`

Which of these parameter combinations are unrealistic? Why?

    An address space of 32 bytes with a physical memory of 1m seems like a small address space and pagesize. An address space of 256m with a page size of 1m seems like page size is really small.

4. Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?

    physical memory must be larger than address space, page size can't be larger than address space (but it can be the same size)
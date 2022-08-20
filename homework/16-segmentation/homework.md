[segmentation.py README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-segmentation/README.md)

1. First let’s use a tiny address space to translate some addresses. Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?

    At first I got all screwed up by offsets here. Broke off the offset and was using that to determine if an address was valid. Really it was much simpler. Just turn the decimal into binary, get the lead bit to determine segment, then take the decimal supplied in parenthesis and compare that to the segments address space.

`segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0`

    ```sh
    ARG seed 0
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:
    valid seg0 virtual addresses = 0-19
    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    valid seg1 virtual addresses = 108-127
    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x0000006c (decimal:  108) --> PA or segmentation violation? 1 101100 valid
    VA  1: 0x00000061 (decimal:   97) --> PA or segmentation violation? 1 100001 invalid
    VA  2: 0x00000035 (decimal:   53) --> PA or segmentation violation? 0 110101 invalid
    VA  3: 0x00000021 (decimal:   33) --> PA or segmentation violation? 0 100001 invalid
    VA  4: 0x00000041 (decimal:   65) --> PA or segmentation violation? 1 000001 invalid
    ```

`segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`

    ```sh
    ARG seed 1
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0) 0-19
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x00000011 (decimal:   17) --> PA or segmentation violation? 0 10001 valid
    VA  1: 0x0000006c (decimal:  108) --> PA or segmentation violation? 1 01100 valid
    VA  2: 0x00000061 (decimal:   97) --> PA or segmentation violation? 1 00001 invalid
    VA  3: 0x00000020 (decimal:   32) --> PA or segmentation violation? 0 00000 invalid
    VA  4: 0x0000003f (decimal:   63) --> PA or segmentation violation? 0 11111 invalid
    ```
`segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2`

    ```sh
    ARG seed 2
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x0000007a (decimal:  122) --> PA or segmentation violation? 1 111010 valid
    VA  1: 0x00000079 (decimal:  121) --> PA or segmentation violation? 1 111001 valid
    VA  2: 0x00000007 (decimal:    7) --> PA or segmentation violation? 0 000111 valid
    VA  3: 0x0000000a (decimal:   10) --> PA or segmentation violation? 0 001010 valid
    VA  4: 0x0000006a (decimal:  106) --> PA or segmentation violation? 1 101010 invalid
    ```

2. Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and highest illegal addresses in this entire address space? Finally, how would you run `segmentation.py` with the `-A` flag to test if you are right?

    seg0 valid virtual = 0-19
    seg0 valid physical = 0-19

    seg1 valid virtual = 108-127
    seg1 valid physical = 492-511

    ```sh
    mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/homework/16-segmentation (master)$ python3 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -A 19,108,20,107 -c
    ARG seed 2
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x00000013 (decimal:   19) --> VALID in SEG0: 0x00000013 (decimal:   19)
    VA  1: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
    VA  2: 0x00000014 (decimal:   20) --> SEGMENTATION VIOLATION (SEG0)
    VA  3: 0x0000006b (decimal:  107) --> SEGMENTATION VIOLATION (SEG1)
    ```

3. Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters: `segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 ? --l0 ? --b1 ? --l1 ?`

    `segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2 -c`

4. Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). How should you configure the simulator to do so? Which parameters are important to getting this outcome?

    set each segments bounds to be half the address space each
    `python3 ./segmentation.py -a 16 -p 64 -n 10 --l0 7 --l1 8 -c`

5. Can you run the simulator such that no virtual addresses are valid? How?

    Set the limits to 0.
    `python3 ./segmentation.py -a 16 -p 64 -n 10 --l0 7 --l1 8 -c`

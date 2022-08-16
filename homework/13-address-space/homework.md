## Homework Questions
1. The first Linux tool you should check out is the very simple tool free. First, type `man free` and read its entire manual page; it’s short, don’t worry!

2. Now, run `free`, perhaps using some of the arguments that might be useful (e.g., `-m`, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

  ```sh
  mike@DESKTOP-EO1SSPM ~/projects/ostep-homework (master)$ free -m
                total        used        free      shared  buff/cache   available
  Mem:          12744         993       11161           0         589       11499
  Swap:          4096           0        4096
  ```
  Seems to match expectations

3. Next, create a little program that uses a certain amount of memory,called `memory-user.c`. This program should take one command-line argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.

  See `memory-user.c`

4. Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations?  Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
  Before running `./memory-user 1000  100`

  ```sh
  mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/homework/13-address-space (master)$ free -m
                total        used        free      shared  buff/cache   available
  Mem:          12744         691       11677           0         375       11808
  Swap:          4096           0        4096
  ```

  After running ./memory-user 1000  100

  ```sh
  mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/homework/13-address-space (master)$ free -m
                total        used        free      shared  buff/cache   available
  Mem:          12744        1694       10674           0         375       10805
  Swap:          4096
  ```

  Looking at the free memory, I lost what was expected, and after the process dies that memory is reclaimed. What's weird is running larger memory allocations than I have don't lead to segfaults, which some other folks have seen. Before I put in a check of the `malloc` return, the program was just silently failing. Once I put in the `malloc` check I can get actual failures.

5. Let’s try one more tool, known as `pmap`. Spend some time, and read the `pmap` manual page in detail.

6. To use `pmap`, you have to know the process ID of the process you’re interested in. Thus, first run `ps auxw` to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your `memory-user` program in this case (indeed, you can even have that program call `getpid()` and print out its PID for your convenience).

  Not running much interesting stuff in my WSL distro. Literally running nothing outside of vscode server, which has a ton of stuff going on when I run `pmap -x {pid}`

7. Now run `pmap` on some of these processes, using various flags (like `-X`) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

  anon - allocated memory via malloc or mmap
  so files - shared library files for linux
  stack - stack memory

8. Finally, let’s run `pmap` on your memory-user program, with different amounts of used memory. What do you see here? Does the output from `pmap` match your expectations?

  ```sh
  mike@DESKTOP-EO1SSPM ~/projects/ostep-homework/homework/13-address-space (master)$ ./memory-user 1000 100 & sleep 1 && pmap -x "$!"
  [1] 4299
  pid: 4299
  mem: 1048576000
  clock start: 555
  4299:   ./memory-user 1000 100
  Address           Kbytes     RSS   Dirty Mode  Mapping
  000055d09aa59000       4       4       0 r---- memory-user
  000055d09aa5a000       4       4       0 r-x-- memory-user
  000055d09aa5b000       4       4       0 r---- memory-user
  000055d09aa5c000       4       4       4 r---- memory-user
  000055d09aa5d000       4       4       4 rw--- memory-user
  000055d09b7a9000     132       4       4 rw---   [ anon ]
  00007fed800fa000 4096004 1006616 1006616 rw---   [ anon ]
  00007fee7a0fb000     136     136       0 r---- libc-2.31.so
  00007fee7a11d000    1504     972       0 r-x-- libc-2.31.so
  00007fee7a295000     312     172       0 r---- libc-2.31.so
  00007fee7a2e3000      16      16      16 r---- libc-2.31.so
  00007fee7a2e7000       8       8       8 rw--- libc-2.31.so
  00007fee7a2e9000      24      20      20 rw---   [ anon ]
  00007fee7a2fa000       4       4       0 r---- ld-2.31.so
  00007fee7a2fb000     140     140       0 r-x-- ld-2.31.so
  00007fee7a31e000      32      32       0 r---- ld-2.31.so
  00007fee7a327000       4       4       4 r---- ld-2.31.so
  00007fee7a328000       4       4       4 rw--- ld-2.31.so
  00007fee7a329000       4       4       4 rw---   [ anon ]
  00007ffe9f32c000     136      16      16 rw---   [ stack ]
  00007ffe9f37b000      12       0       0 r----   [ anon ]
  00007ffe9f37e000       8       4       0 r-x--   [ anon ]
  ---------------- ------- ------- -------
  total kB         4098500 1008172 1006700
  ```

  Looks like a block was allocated to anon. Matches expectations. Side story, but that command, `./memory-user 1000 100 & sleep 1 && pmap -x "$!"` is pretty nifty. Borrowed from other repos. `$!` contains the process id of the most recently executed background pipeline.
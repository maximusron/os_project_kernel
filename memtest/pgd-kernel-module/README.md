# Kernel Modules for PGD and Memory Layout

This is an experiment on kernel modules which is tested on Ubuntu 18.04 LTS (shipped with kernel version 4.15). 
There are two modules in the repository:
1. `mem_module.c` prints out memory layout of a process, namely start and end addresses of code, heap, stack and data section in memory.
2. `pgd_module.c` prints out top level page table of a process. For more info page table management: [Page Table Management](https://www.kernel.org/doc/gorman/html/understand/understand006.html)

Implemented together with [Buğra Aydın](https://github.com/bugraaydin/)

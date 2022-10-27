#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
// #include <stdlib.h>
// #include <stdio.h>

#define OK 0
#define MEM_OPTION 1
struct Mem
{
    int offset;
    int size;
    int allocated;
};
typedef struct Mem mem;

mem arr[10];
int sizes[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 5};

static void printmem(void)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printk(KERN_NOTICE "%d: offset: %d, size: %d, allocated: %d\n", i, arr[i].offset, arr[i].size, arr[i].allocated);
    }
}


static void memCheck(int size)
{
    int choice = 0;
    printk(KERN_INFO "MEMCHECK_MODE : BEST_FIT");
        int bestPos = -1;
        int bestRem = INT_MAX;
        int i;
        for (i = 0; i < 10; i++)
        {
            int rem = arr[i].size - arr[i].allocated;
            if (rem >= size)
            {
                if (rem < bestRem)
                {
                    bestRem = rem;
                    bestPos = i;
                }
            }
        }
        printk(KERN_NOTICE "memory available at position %d\n", bestPos);
}



static int __init mochi_hw_init(void) {
  printk(KERN_CRIT "Initializing Kernel...\n");
  printk(KERN_CRIT "The process is \"%s\" (pid %i)\n",
        current->comm, current->pid);
  printk(KERN_CRIT "Starting memory allocation\n");

 int i;
  for (i = 0; i < 10; i++)
    {
        arr[i].offset = (i == 0) ? 0 : (arr[i - 1].offset + arr[i - 1].size);
        arr[i].size = sizes[i];
        arr[i].allocated = 0;
    }

    printk(KERN_INFO "initial memory:\n");
    printmem();
    
    int choice = MEM_OPTION;
    for (i = 0; i < 10; i++)
    {     
      printk(KERN_INFO "Looping MEMCHECK, MEMALLOC, MEMFREE");
        int choice = 1;
        if (choice == 1)
        {
            printk(KERN_INFO "SIZE : 4 bytes\n");
            int size = 4;
            memCheck(size);
            choice ++;
        }
        else if (choice == 2)
        {
            printk(KERN_INFO "enter size\n");
            int size;
            // scanf("%d", &size);
            // memAlloc(size);
            choice ++;
        }
        else if (choice == 3)
        {
            printk(KERN_INFO "enter position\n");
            int pos;
            // scanf("%d", &pos);
            // memFree(pos);
            choice = 1;
        }
        else
        {
            printk(KERN_INFO "invalid choice\n");
        }
    }
    
    ///MAIN

  return OK;
}

static void __exit mochi_hw_exit(void) {
  printk(KERN_CRIT "Exiting Kernel Directive\n");
}

module_init(mochi_hw_init);
//intermediate module
module_exit(mochi_hw_exit);


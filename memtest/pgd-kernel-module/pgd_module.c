#include <linux/module.h>	
#include <linux/kernel.h>
#include <linux/pid.h>	
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/highmem.h>
#include <linux/mm.h>
#include <asm/page.h>
#include <linux/sched/task.h> 

static int processid = 2711;

module_param(processid, int, 0);

static void print_pgd(struct mm_struct *mm, long unsigned vm_start);

// given the memory descriptor and the begin address of virtual memory, prints out the top level page table
static void print_pgd(struct mm_struct *mm, long unsigned vm_start) {
	long unsigned current_addr = vm_start;
	long unsigned inc = 1LU << 39;

	pgd_t *pgd; 
	int i = 0; 
	printk(KERN_ERR "TOP LEVEL PAGE TABLE ENTRIES:\n");
	for (; i < (1<<9); ++i) {
		// pgd_offset() takes an address and the mm_struct for the process 
		// and returns the PGD entry that covers the requested address.
		pgd = pgd_offset(mm, current_addr);
		if (pgd_none(*pgd) || pgd_bad(*pgd)) {
			printk(KERN_ERR "ENTRY %d, PGD: %lu - DOES NOT EXIST OR BAD\n", i, pgd->pgd);
			break;
		}
		else {
			printk(KERN_INFO "ENTRY %d, PGD: %lu", i, pgd->pgd);
		}
		current_addr += inc;
	}
} 

static int __init test_init(void) {
	struct task_struct *task;
	
	task = get_pid_task(find_vpid(processid), PIDTYPE_PID);
	struct mm_struct *mm = task->mm;
	struct vm_area_struct *vma = mm->mmap;

	if (task == NULL){
		printk(KERN_INFO "\nGIVEN PID %d WAS NOT FOUND, TERMINATING\n", processid);
		return 0;
	}

	if (task->pid == processid){
		printk(KERN_INFO "-----------------------------------------------");
		printk(KERN_INFO "\nGIVEN PID %d IS FOUND.\n",task->pid);
		print_pgd(mm, vma->vm_start);
	}

	return 0;
}

static void __exit test_exit(void) {
	printk(KERN_INFO "GOODBYE WORLD.\n");
	printk(KERN_INFO "-----------------------------------------------");
}

module_init(test_init); // init macro
module_exit(test_exit); // exit macro
MODULE_LICENSE("GPL");
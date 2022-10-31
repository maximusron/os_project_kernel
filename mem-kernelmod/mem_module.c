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

static int is_stack(struct vm_area_struct *vma) 
{
	return vma->vm_start <= vma->vm_mm->start_stack &&
		vma->vm_end >= vma->vm_mm->start_stack;
}

static void print_task(struct task_struct *task){

	struct mm_struct *mm = task->mm;
	struct vm_area_struct *vma = mm->mmap;
	int total_vma_used = 0;

	while(vma != NULL){
		// stack
		if(is_stack(vma)){
			printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %luB  ~~STACK\n", vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start)/8);
			vma = vma->vm_next;
			total_vma_used++;
			continue;
		}
		// code
		else if(vma->vm_start <= mm->end_code && vma->vm_end >= mm->start_code){
			printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu  ~~CODE\n", vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start));
		}	
		// data
		else if(vma->vm_start <= mm->end_data && vma->vm_end >= mm->start_data){
			printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu  ~~DATA\n", vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start));
		}
		// heap
		else if (vma->vm_start <= mm->brk && vma->vm_end >= mm->start_brk){
			printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu  ~~HEAP\n", vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start)); 		
		}
		else {
			printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu\n", vma->vm_start, vma->vm_end, (vma->vm_end - vma->vm_start)); 
		}
		total_vma_used++;
		vma = vma->vm_next;
	}

	printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu ~~ MAIN ARGS\n", mm->arg_start, mm->arg_end, mm->arg_end - mm->arg_start); // start and end of the main
	printk(KERN_INFO "START--> 0x%016lx ~ END--> 0x%016lx, SIZE--> %lu ~~ ENVIRONMENT VARIABLS\n", mm->env_start, mm->env_end, mm->env_end - mm->env_start); // start and end of the environment
	printk(KERN_INFO "%lu  ~~RSS\n", get_mm_rss(mm)); // rss
	printk(KERN_INFO "%lu ~~TOTAL PAGES MAPPED\n", mm->total_vm); // total vm
	printk(KERN_INFO "%d ~~TOTAL VM_AREA_STRUCTS USED\n", total_vma_used);
}

static int __init test_init(void) {
  printk(KERN_CRIT "Initializing Kernel...\n");

	struct task_struct *task;
	task = get_pid_task(find_vpid(processid), PIDTYPE_PID);

	if (task == NULL){
		printk(KERN_INFO "\nGIVEN PID %d WAS NOT FOUND, TERMINATING\n", processid);
		return 0;
	}

	if (task->pid == processid){
		printk(KERN_INFO "-----------------------------------------------");
		printk(KERN_INFO "\nGIVEN PID %d IS FOUND.\n",task->pid);
	}

	print_task(task);
	return 0;
}

static void __exit test_exit(void) {
	printk(KERN_INFO "GOODBYE WORLD.\n");
	printk(KERN_INFO "-----------------------------------------------");
}

module_init(test_init); // init macro
module_exit(test_exit); // exit macro
MODULE_LICENSE("GPL");

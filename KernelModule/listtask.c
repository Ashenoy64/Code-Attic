
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void dfs(struct task_struct *task,int indent)
{
  struct task_struct *task_next;
  struct list_head *list;

  list_for_each(list, &task->children) {
    task_next = list_entry(list, struct task_struct, sibling);
    for (int i=0; i<indent; i++) 
    {
     	if (i%2 == 0 || i == 0)
        	printk(KERN_CONT"%c", '|');
        else
                printk(KERN_CONT" ");
    }
	printk(KERN_CONT"%c%c", '|', '_');
    printk(KERN_CONT "pid: %d | pname: %s | state: %ud\n", task_next->pid, task_next->comm, task_next->__state);

    dfs(task_next,indent+2);
  }  
}

int tasks_lister_dfs_init(void)
{
  printk(KERN_INFO "Loading module...\n");

  dfs(&init_task,0);

  printk(KERN_INFO "Module loaded.\n");
  return 0;
}

void tasks_lister_dfs_exit(void)
{
  printk(KERN_INFO "Module removed.\n");
}

module_init(tasks_lister_dfs_init);
module_exit(tasks_lister_dfs_exit);
MODULE_LICENSE("GPL");

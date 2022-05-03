#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

int len,temp;
char *msg;

static ssize_t read_proc(struct file* filp, char* buf, size_t count, loff_t* offp );
static ssize_t write_proc(struct file* filp,const char* buf, size_t count, loff_t* offp);
// struct proc_dir_entry *proc_file_entry;


static struct proc_ops my_fops;

static struct proc_ops my_fops = {

        .proc_read = read_proc,
        .proc_write = write_proc
};



static ssize_t read_proc(struct file* filp, char* buf, size_t count, loff_t* offp ) {
	
	if(count>temp) {
		count=temp;
	}

	temp=temp-count;
	copy_to_user(buf,msg, count);
	
	if(count==0)
		temp=len;
   
	return count;
}

static ssize_t write_proc(struct file* filp,const char* buf, size_t count, loff_t* offp) {
	
	copy_from_user(msg,buf,count);
	len=count;
	temp=len;
	return count;
}

void create_new_proc_entry(void) {
	
	proc_create("helloqwerty", 0, NULL, &my_fops);
	msg=(char*)kmalloc(10*sizeof(char),GFP_KERNEL);
}


int proc_init(void) {

	create_new_proc_entry();
	return 0;

}

void proc_cleanup(void) {

	remove_proc_entry("helloqwerty",NULL);
	kfree(msg);

}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);

#ifndef		__PROC_H__
#define		__PROC_H__

#include <list.h>

typedef int pid_t;

enum p_state {
	PROC_UNUSED,
	PROC_RUN,	
	PROC_STOP,
	PROC_ZOMBIE,
	PROC_BLOCK,
};

#pragma pack(push, 1)

struct proc_option
{
	unsigned priority;
};

struct process
{
	pid_t pid;						//process id
	void *stack;					//stack for esp
	void *pd;						//page directory
	enum p_state state;				// process state
	unsigned long long time_sleep;	

	unsigned char priority;		
	unsigned time_slice;	

	struct list_elem elem_all;		
	struct list_elem elem_stat;	

	unsigned long long time_used;	
	unsigned long long time_sched;
	struct process* parent;		
	int simple_lock;		
	int child_pid;		
	int exit_status;
};

#pragma pack(pop)

extern struct process *cur_process;	

typedef void proc_func(void* aux);	
proc_func print_pid;			
proc_func idle;					

void schedule(void);			

void init_proc(void);			
void proc_free(void);			

pid_t proc_create(proc_func func, struct proc_option *priority, void* aux);
void proc_wake(void);			
void proc_sleep(unsigned ticks);
void proc_block(void);			
void proc_unblock(struct process* proc);

void proc_print_data(void);		
#endif

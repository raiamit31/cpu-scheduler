extern struct process{
	int a_time, cpu_burst, r_time, priority, pid;
	struct process *next;
} *head;



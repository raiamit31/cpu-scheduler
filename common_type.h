extern struct process{
	int a_time, cpu_burst, r_time, priority, pid;
	struct process *next;
} *head;

extern struct gantt_chart{
	int process_id, start, end;
	struct gantt_chart *next;
} *header, *trailer;

struct process{
	int pid, a_time, cpu_burst, r_time, priority, response_time, waiting_time, tat;
	struct process *next;
};

struct gantt_chart{
	int process_id, start, end;
	struct gantt_chart *next;
};



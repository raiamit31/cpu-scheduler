
// fcfs.cpp
void fcfs_init( void );

// sjf.cpp
void sjf_init( void );

// priority.cpp
void priority_init( void );

// rRobin.cpp
void rRobin_init( void );

// chart.cpp
void add_node_gantt_chart( int, int, int );
void print_gantt_chart( void );

// common.cpp
void add_queue( struct process *, struct process * );
void print_table( struct process * );
void remove_node( struct process *, struct process * );
void get_process( int, int );
void add_process( struct process *, int  );
void print_process( int, const char * );
void sort_ready_queue( struct process * );
void calculate_response_time( struct gantt_chart *, struct process * );
void calculate_waiting_tat( struct gantt_chart *, struct process * );
void average_time( struct process *, int );

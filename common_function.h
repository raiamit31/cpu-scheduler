

void print_table( struct process * );
void fcfs_init( void );
void sjf_init( void );
void priority_init( void );
void rRobin_init( void );
void add_queue( struct process *, struct process * );
void remove_node( struct process *, struct process * );

void get_process( int, int );
void add_process( struct process *, int  );

void print_process( int, char * );

void add_node_gantt_chart( int, int, int );
void print_gantt_chart( void );




void fcfs_init( void );
void sjf_init( void );
void priority_init( void );
void rRobin_init( void );
void add_queue( struct process *, struct process * );
void remove_node( struct process *, struct process * );
void print_process( int );

void get_process( int, int );
void add_process( struct process *, int  );


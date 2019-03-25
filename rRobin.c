#include<stdio.h>
#include<stdlib.h>


struct process{
	int a_time, cpu_burst, r_time, pid;
	struct process *next;
} *head = NULL;

void get_process( int );
void print_process( int );
void add_process( struct process * );
void schedule( int );
struct process* find_process( int, int, struct process * );
void add_queue( struct process *, struct process * );
void remove_node( struct process *, struct process * );
void insert_after( struct process *, struct process * );
struct process * search_end( struct process *, int );

int main( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process );
	print_process( n_process );
	schedule( n_process );
	print_process( n_process );
	return 0;
}

void get_process( int n )
{
	struct process *temp = NULL;
	for( int i = 1; i<=n; i++)
	{
		temp = ( struct process * )( malloc( sizeof( struct process ) ) );
		temp->pid = i;
		printf("Enter the details of process \'P%d\'\n", i);
		printf("Arrival time : ");
	        scanf("%d",&temp->a_time );
		printf("CPU burst : ");
	        scanf("%d",&temp->cpu_burst );

		temp->r_time = temp->cpu_burst;
		add_process( temp );
	} // for
}

void add_process( struct process *p )
{
	if( head == NULL )
		head = p;
	else
	{
		struct process *temp, *q = NULL;
		for( temp = head; temp != NULL; temp = temp->next )
		{
			if( p->a_time < temp->a_time )
				break;
			else if ( p->a_time == temp->a_time )
			{
				if( p->cpu_burst < temp->cpu_burst )
					break;
				
			}
			q = temp;		
		} // for
		if( q == NULL )
		{
			p->next = head;
			head = p;
		} //if
		else if( temp == NULL )
			q->next = p;
		else{
			p->next = temp;
			q->next = p;
		}
	} // else
} // add_process

void print_process( int n ) // change the declaration to print_process( void );
{
	if( !n )
		return;
	struct process *temp = head;
	while( temp->next != NULL )
	{
		printf("P%d --> ", temp->pid);
		temp = temp->next;
	} //while
	printf("P%d\n", temp->pid);
} // print_process

void schedule( int n_process )
{

	if( !n_process )
		return;

	struct process *current_process = head, *inter_node = NULL, *queue = NULL;
	int record_time = head->a_time, clock = head->a_time, quant = 0;

	for( ; quant == 0 ; scanf("%d", &quant ) )
		printf("Enter time quanta : ");

	while( head != NULL )
	{
		clock++;
		record_time = ( current_process == NULL ) ? clock : record_time;

		if( current_process != NULL )
		{
			current_process->r_time--;
			
			if( current_process->r_time == 0 )
			{
				if( queue == NULL )
					queue = current_process;
				else
					add_queue( queue, current_process );

				remove_node( head, current_process );

				record_time = clock;
			}
		} // if

		if( !((clock - record_time ) % quant ) ){

			inter_node = search_end( head, clock );
			if( current_process == head )
			{
				if( inter_node != current_process )
				{
					head = head->next;
					insert_after( inter_node, current_process );
					current_process = head;
				}
			}
			else if( head != NULL && head->a_time <= clock )
				current_process = head;
			else
				current_process = NULL;

			record_time = clock;
		}
	} // while
	head = queue;
} // schedule


struct process* find_process( int s, int e, struct process *h )
{
	int smallest = h->cpu_burst;
        struct process *temp = h;
	h = h->next;
	while( h != NULL )
	{
		if( h->a_time <= e )
		{
			if( h->cpu_burst < smallest )
			{
				smallest = h->cpu_burst;
			        temp = h;	
			}  // if 
		} // if 

		h = h->next;
	} // while
	return temp;
}// find_process

void add_queue( struct process *h, struct process *p )
{
	for( ; h->next != NULL ; h = h->next );
	h->next = p;
} // add_queue


void remove_node( struct process *h, struct process *p )
{
	if( h == p )
	{
		if( h->next == NULL )
			head = NULL;
		else
			head = head->next;
	}
	else{
	for( ; h->next != p ; h = h->next );
	h->next = p->next;
	}
	p->next = NULL;
} // remove_node

void insert_after( struct process *IN, struct process *p )
{
	if( IN->next = NULL )
	{
		IN->next = p;
		p->next = NULL;
	}
	else{
		p->next = IN->next;
		IN->next = p;
	}
} // insert_after

struct process *  search_end( struct process *h, int clock )
{
	struct process *q = NULL;

	for(; h!= NULL && h->a_time <= clock; h = h->next )
		q = h;

	return q;
}

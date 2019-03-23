#include<stdio.h>
#include<stdlib.h>


struct process{
	int a_time, cpu_burst, pid;
	struct process *next;
} *head = NULL;

void get_process( int );
void print_process( int );
void add_process( struct process * );
void schedule( void );
struct process* find_process( int, int, struct process * );
void add_queue( struct process *, struct process * );
void remove_node( struct process *, struct process * );


int main( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process );
	print_process( n_process );
	schedule( );
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
				if( p->cpu_burst <= temp->cpu_burst )
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
	struct process *temp = head;
	while( temp->next != NULL )
	{
		printf("P%d --> ", temp->pid);
		temp = temp->next;
	} //while
	printf("P%d\n", temp->pid);
} // print_process

void schedule( void )
{
	int start = head->a_time, end = head->a_time + head->cpu_burst;
	struct process *queue = head, *temp = NULL;

	head = head->next;

	queue->next = NULL;
	printf("%d\n", queue->cpu_burst);
	while( head != NULL )
	{
		printf("%d\n", head->cpu_burst);
		temp = find_process( start, end, head );
		end += temp->cpu_burst;
		add_queue( queue, temp ); // adding temp first because if removed first then until it is added to the queue
					 // there will be no reference to it, so it might get lost.
		remove_node( head, temp );
	}

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

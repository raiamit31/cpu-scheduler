#include<stdio.h>
#include<stdlib.h>


struct process{
	int a_time, cpu_burst, r_time, priority, pid;
	struct process *next;
} *head = NULL;

void get_process( int );
void print_process( int );
void add_process( struct process * );
void schedule( int );
struct process* find_process_priority( int, struct process * );
void add_queue( struct process *, struct process * );
void remove_node( struct process *, struct process * );


int main( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process );
	printf("Oder of arrival : ");
	print_process( n_process );
	schedule( n_process );
	printf("\nOrder of termination : ");
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
		printf("Priority : " );
		scanf("%d", &temp->priority );

		temp->r_time = temp->cpu_burst;
		
		add_process( temp );
	} // for
}

// add_process is different from other scheduling algorithms

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
				if( p->priority <= temp->priority )
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

	struct process *current_process = head, *queue = NULL, *temp = NULL;
	int clock = head->a_time, pr = current_process->priority;
	while( head != NULL )
	{
		clock++;
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

			}
		}
		current_process = find_process_priority( clock, head );
	} // while
	head = queue;
} // schedule


struct process* find_process_priority( int clock, struct process *h )
{
	struct process *temp = NULL;
	for( ; h != NULL; h = h->next )
	{
		if( h->a_time <= clock ){
			if( temp == NULL )
				temp = h;
			else if( temp->priority < h->priority )
				temp = h;
		} // if
	} // for
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

#include<stdio.h>
#include<stdlib.h>


struct process{
	int a_time, cpu_burst, pid;
	struct process *next;
} *head = NULL;

void get_process( int );
void print_process( );
void add_process( struct process * );
void print_table( struct process * );
int main( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process );
	print_process( n_process );
	print_table( head );
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

void print_process( void ) // change the declaration to print_process( void );
{
	struct process *temp = head;
	while( temp->next != NULL )
	{
		printf("P%d --> ", temp->pid);
		temp = temp->next;
	} //while
	printf("P%d\n", temp->pid);
} // print_process

void print_table( struct process *p )
{
	printf("| PROCESS | ARRIVAL TIME | CPU BURST |\n");
	for(; p != NULL ; p = p->next )
		printf("|   P%3d  |     %3d      |   %3d     |\n", p->pid, p->a_time, p->cpu_burst);
}

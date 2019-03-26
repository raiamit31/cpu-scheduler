#include<stdio.h>
#include<stdlib.h>
#include"common_type.h"
#include"common_function.h"


void get_process( int n, int choice )
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


		switch( choice )// options that are specific to different scheduling algorithms, case number is according to main.c
		{
			case 1:
			case 2:
			case 4:
				temp->priority = 0;
				break;

			case 3:
				printf("Priority : " );
				scanf("%d", &temp->priority );

				break;

		} //switch

		temp->r_time = temp->cpu_burst; //used in priority and rRobin
		add_process( temp, choice );
	} // for
}


void add_process( struct process *p, int choice )
{
	if( head == NULL )
		head = p;
	else
	{
		struct process *temp, *q = NULL;
		int loop_break = 0;
		for( temp = head; temp != NULL; temp = temp->next )
		{
			if( p->a_time < temp->a_time )
				break;
			else if ( p->a_time == temp->a_time )
			{
				switch( choice ) // options that are specific to different scheduling algorithms, case number is according to main.c
				{
					case 1:
					case 2:
					case 4:
						if( p->cpu_burst < temp->cpu_burst )
							loop_break = 1;
						break; //case break
					case 3:
						if( p->priority < temp->priority )
							loop_break = 1;
						else if( p->priority == temp->priority )
						{
							if( p->cpu_burst < temp->cpu_burst )
								loop_break = 1;
						}
						break; //case break
				} //switch

				if( loop_break )
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

void add_queue( struct process *h, struct process *p )
{
	for( ; h->next != NULL ; h = h->next );
	h->next = p;
} // add_queue


void remove_node( struct process *h, struct process *p )
{
	extern struct process *head;
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

void print_process( int n, char *c ) // change the declaration to print_process( void );
{
	if( !n )
		return;
	printf("%s : ", c );
	struct process *temp = head;
	while( temp->next != NULL )
	{
		printf("P%d --> ", temp->pid);
		temp = temp->next;
	} //while
	printf("P%d\n\n", temp->pid);
} // print_process


void print_table( struct process *p )
{
	if( p == NULL )
		return;

	printf("| PROCESS | ARRIVAL TIME | CPU BURST | PRIORITY |\n");
	for(; p != NULL ; p = p->next )
		printf("|   P%-3d  |     %3d      |   %3d     |   %3d    |\n", p->pid, p->a_time, p->cpu_burst, p->priority);
}

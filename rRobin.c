#include<stdio.h>
#include<stdlib.h>

#include "common_type.h"
#include "common_function.h"

void schedule_rRobin( int );
void insert_after( struct process *, struct process * );
struct process * search_end( struct process *, int );

void rRobin_init( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process, 4 );
	print_process( n_process, "\nOrder of arrival" );
	print_table( head );
	schedule_rRobin( n_process );
	print_process( n_process, "\nOrder of termination" );
}

void schedule_rRobin( int n_process )
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

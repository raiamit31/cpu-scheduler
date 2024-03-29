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

	printf("---------------------------------------------------------------------------------------------------------------------\n");
	
	print_process( n_process, "\nOrder of arrival" );

	schedule_rRobin( n_process );

	print_process( n_process, "Order of termination" );

	printf("\n=== Gantt chart ===\n");
	print_gantt_chart();
	printf("\n");

	sort_ready_queue( head );	
	calculate_response_time( header, head );
	calculate_waiting_tat( header, head );

	print_table( head );

	printf("\n");
	average_time( head, n_process );	
	printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void schedule_rRobin( int n_process )
{

	if( !n_process )
		return;

	struct process *current_process = head, 
		       *inter_node = NULL, *queue = NULL;

	int record_time = head->a_time, 
	    clock = head->a_time, 
	    quant = 0, start_t = head->a_time;

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

				add_node_gantt_chart( start_t, clock, current_process->pid ); // add  process to gantt chart
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
					add_node_gantt_chart( start_t, clock, current_process->pid ); // add process to gantt chart
					current_process = head;
					start_t = clock;
				}
			}
			else if( head != NULL && head->a_time <= clock ){
				current_process = head;
				start_t = clock;
			}
			else
				current_process = NULL;

			record_time = clock;
		}
	} // while
	head = queue;
} // schedule


void insert_after( struct process *IN, struct process *p )
{
	if( IN->next == NULL )
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

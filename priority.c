#include<stdio.h>
#include<stdlib.h>

#include "common_type.h"
#include"common_function.h"

void schedule_priority( int );
struct process* find_process_priority( int, struct process * );

void priority_init( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process, 3 );


	printf("---------------------------------------------------------------------------------------------------------------------\n");
	print_process( n_process, "\nOrder of arrival" );

	schedule_priority( n_process );
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

void schedule_priority( int n_process )
{

	if( !n_process )
		return;	

	struct process *current_process = head, *queue = NULL, *temp = NULL;

	int clock = head->a_time, 
	    pr = current_process->priority, 
	    start_t = current_process->a_time;

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

			//	add_node_gantt_chart( start_t, clock, current_process->pid );

				remove_node( head, current_process );

			}
		}
		temp = find_process_priority( clock, head );

		if( temp != current_process )
		{
			add_node_gantt_chart( start_t, clock, current_process->pid );
			start_t = clock;
		}
		current_process = temp;
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

	

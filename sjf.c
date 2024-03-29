#include<stdio.h>
#include<stdlib.h>

#include "common_type.h"

#include "common_function.h"
struct process* find_process( int, int, struct process * );
void schedule_sjf( int );

void sjf_init( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process, 2 );

	printf("---------------------------------------------------------------------------------------------------------------------\n");
	print_process( n_process, "\nOrder of arrival" );

	schedule_sjf( n_process );

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

void schedule_sjf( int n_process )
{

	if( !n_process )
		return;
	int start = head->a_time, 
	    end = head->a_time + head->cpu_burst;
	
	add_node_gantt_chart(start, end, head->pid ); // first node added from here
	
	struct process *queue = head, *temp = NULL;
	
	head = head->next;
	queue->next = NULL;

	while( head != NULL )
	{
		printf("%d\n", head->cpu_burst);
		temp = find_process( start, end, head );
		
		if( temp->a_time <= end )
		add_node_gantt_chart( end, end + temp->cpu_burst, temp->pid);
		
		else
		{
			add_node_gantt_chart( temp->a_time, temp->a_time + temp->cpu_burst, temp->pid);
			end = temp->a_time;
		}
		
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




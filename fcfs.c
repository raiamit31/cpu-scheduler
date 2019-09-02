#include<cstdio>
#include<cstdlib>
#include<iostream>
#include "common_type.h"
#include"extern_declaration.h"
#include "common_function.h"


void schedule_fcfs( void );

void fcfs_init( void )
{
	int n_process;
	std::cout << "Enter the number of process : ";
	scanf("%d", &n_process);

	get_process( n_process, 1 );

	printf("------------------------------------------"\
	"--------------------------------------------------"\
	"------------------------\n");
	
	print_process( n_process, "\nOrder of arrival" );

	schedule_fcfs();

	print_process( n_process, "Order of termination" );

	printf("\n=== Gantt chart ====\n");
	print_gantt_chart();
	std::cout << std::endl;
	
	sort_ready_queue( head );

	calculate_response_time( header, head );
	calculate_waiting_tat( header, head );
	print_table( head );
	
	std::cout << std::endl;
	average_time( head, n_process );

	printf("-----------------------------------------"\
	"--------------------------------------------------"\
	"------------------------\n");
} //fcfs_init

void schedule_fcfs( void )
{
	if( head == NULL )
		return;

	int start = head->a_time, end = start + head->cpu_burst;

	add_node_gantt_chart( start, end, head->pid );
	struct process *current_process = NULL, *queue = head;

	head = head->next;
	queue->next = NULL;

	while( head != NULL )
	{
		if( head->a_time <= end )
			add_node_gantt_chart( end, end + head->cpu_burst, head->pid );
		else{
			add_node_gantt_chart( head->a_time, head->a_time + head->cpu_burst, head->pid );
			end = head->a_time;
		}
		end += head->cpu_burst;

		add_queue( queue, head );
		remove_node( head, head );
	}

	head = queue;

} //schedule_fcfs

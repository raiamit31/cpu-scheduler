#include<stdio.h>
#include<stdlib.h>
#include "common_type.h"
#include "common_function.h"

void print_table( struct process * );

void fcfs_init( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process, 1 );
	print_process( n_process );
	print_table( head );
}

void print_table( struct process *p )
{
	printf("| PROCESS | ARRIVAL TIME | CPU BURST |\n");
	for(; p != NULL ; p = p->next )
		printf("|   P%3d  |     %3d      |   %3d     |\n", p->pid, p->a_time, p->cpu_burst);
}

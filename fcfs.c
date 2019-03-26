#include<stdio.h>
#include<stdlib.h>
#include "common_type.h"
#include "common_function.h"


void fcfs_init( void )
{
	int n_process;
	printf("Enter the number of process : ");
	scanf("%d", &n_process);

	get_process( n_process, 1 );
	print_process( n_process, "\nOrder of arrival" );
	print_table( head );
	print_process( n_process, "\nOrder of termination" );
}


#include<stdio.h>
#include<stdlib.h>

struct process{
	int pid, a_time, cpu_burst, r_time, priority, response_time, waiting_time, tat;
	struct process *next;
} *head;

struct gantt_chart{
	int process_id, start, end;
	struct gantt_chart *next;
} *header = NULL, *trailer = NULL;


#include "common_function.h"
void release( void );


int main( void )
{
	int choice;
	printf("\n======== CPU SCHEDULING ========\n\n");
	printf("1) First come, First serve\n");
	printf("2) Shortest job first\n");
	printf("3) Priority\n");
	printf("4) Round Robin\n");
	printf("5) Exit\n");

	do{
		printf("\nEnter your choice : ");
		scanf("%d", &choice );

		switch( choice )
		{
			case 1:
				fcfs_init();
				break;

			case 2:
				sjf_init();
				break;

			case 3:
				priority_init();
				break;

			case 4:
				rRobin_init();
				break;

			case 5:
				choice = 0;
				break;
			case 0:
				choice = -1;
			default:
				printf("Wrong choice, retry!!\n\n");
		} //switch
		release();
		head = NULL;
		header = trailer = NULL;

		// correct this memory leak
	}while ( choice );

	return 0;
}


void release( void )
{
	struct process *temp = NULL;
	struct gantt_chart *c = NULL;

	while( head != NULL )
	{
		temp = head;
		head = head->next;
		free( temp );
	}

	while( header != NULL )
	{
		c = header;
		header = header->next;
		free( c );
	}
} //release

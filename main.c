#include<stdio.h>

struct process{
	int a_time, cpu_burst, r_time, priority, pid;
	struct process *next;
} *head;

#include "common_function.h"

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
		printf("Enter your choice : ");
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
		head = NULL; // change this with to avoid memory leak
	}while ( choice );

	return 0;
}

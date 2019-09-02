#include<cstdio>
#include<cstdlib>
#include<iostream>
#include "common_type.h"
#include "common_function.h"


struct process *head = NULL;
struct gantt_chart *header = NULL, *trailer = NULL;


void release( void );


int main( void )
{
	int choice;
	std::cout << "\n======== CPU SCHEDULING ========\n\n";
	std::cout << "1) First come, First serve\n";
	std::cout << "2) Shortest job first\n";
	std::cout << "3) Priority\n";
	std::cout << "4) Round Robin\n";
	std::cout << "5) Exit\n";

	do{
		std::cout << "\nEnter your choice : ";
		std::cin >> choice;

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
				std::cout << "Wrong choice, retry!!\n\n";
		} //switch
		release();

	}while ( choice );

	return 0;
}// main

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

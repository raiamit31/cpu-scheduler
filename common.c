#include<cstdio>
#include<cstdlib>
#include<iostream>
#include"common_type.h"
#include"extern_declaration.h"
#include"common_function.h"


void get_process( int n, int choice )
{
	struct process *temp = NULL;
	for( int i = 1; i<=n; i++)
	{
		temp = ( struct process * )( malloc( sizeof( struct process ) ) );
		temp->pid = i;
		std::cout << "Enter the details of process \'P" << i << "\'" << std::endl;
		//printf("Arrival time : ");
		std::cout << "Arrival time : ";
	        scanf("%d",&temp->a_time );
		//printf("CPU burst : ");
		std::cout << "CPU burst : ";
	        scanf("%d",&temp->cpu_burst );

		
		// options that are specific to different scheduling algorithms, case number is according to main.c
		switch( choice )
		{
			case 1:
			case 2:
			case 4:
				temp->priority = 0;
				break;

			case 3:
				std::cout << "Priority : ";
				scanf("%d", &temp->priority );
				break;

		} //switch

		temp->r_time = temp->cpu_burst; //used in priority and rRobin
		add_process( temp, choice );
	} // for
}


void add_process( struct process *p, int choice )
{
	if( head == NULL )
		head = p;
	else
	{
		struct process *temp, *q = NULL;
		int loop_break = 0;
		for( temp = head; temp != NULL; temp = temp->next )
		{
			if( p->a_time < temp->a_time )
				break;
			else if ( p->a_time == temp->a_time )
			{
				// options that are specific to different scheduling algorithms, case number is according to main.c
				switch( choice )				{
					case 1:
					case 2:
					case 4:
						if( p->cpu_burst < temp->cpu_burst )
							loop_break = 1;
						break; //case break
					case 3:
						if( p->priority > temp->priority )
							loop_break = 1;
						else if( p->priority == temp->priority )
						{
							if( p->cpu_burst < temp->cpu_burst )
								loop_break = 1;
						}
						break; //case break
				} //switch

				if( loop_break )
					break;
			}
			q = temp;		
		} // for
		if( q == NULL )
		{
			p->next = head;
			head = p;
		} //if
		else if( temp == NULL )
			q->next = p;
		else{
			p->next = temp;
			q->next = p;
		}
	} // else
} // add_process

void add_queue( struct process *h, struct process *p )
{
	for( ; h->next != NULL ; h = h->next );
	h->next = p;
} // add_queue


void remove_node( struct process *h, struct process *p )
{
	extern struct process *head;
	if( h == p )
	{
		if( h->next == NULL )
			head = NULL;
		else
			head = head->next;
	}
	else{
	for( ; h->next != p ; h = h->next );
	h->next = p->next;
	}
	p->next = NULL;
} // remove_node

void print_process( int n, const char *c )
{
	if( !n )
		return;
	printf("%s : ", c );
	struct process *temp = head;
	while( temp->next != NULL )
	{
		std::cout << "P" << temp->pid << " --> ";
		temp = temp->next;
	} //while
	std::cout << "P" << temp->pid << std::endl;
} // print_process


void print_table( struct process *p )
{
	if( p == NULL )
		return;

	printf("| PROCESS | ARRIVAL TIME | CPU BURST | PRIORITY | RESPONSE TIME | WAITING TIME | TURN AROUND TIME |\n");
	for(; p != NULL ; p = p->next )
		printf("|   P%-3d  |     %3d      |   %3d     |   %3d    |     %-3d       |      %-3d     |        %-3d       |\n", 
				p->pid, p->a_time, p->cpu_burst, p->priority, p->response_time, p->waiting_time, p->tat);
}

void sort_ready_queue( struct process *h )
{
	struct process *list = h;
	h = h->next;
	list->next = NULL;

	while( h != NULL )
	{
		struct process *temp = list, *prev = NULL, *hold = h;
		h = h->next;
		hold->next = NULL;

		for( ; temp != NULL && hold->pid > temp->pid; temp = temp->next )
			prev = temp;


		if( prev == NULL )
		{
			hold->next = temp;
			list = hold;
		}
		else if( temp == NULL )
			prev->next = hold;
		else
		{
			prev->next = hold;
			hold->next = temp;
		}
	} //while

	head = list;
} // sort_ready_queue

void calculate_response_time( struct gantt_chart *c, struct process *p )
{
	while( p != NULL )
	{
		struct gantt_chart *temp = c;

		for(; temp != NULL && temp->process_id != p->pid; temp = temp->next );

		p->response_time = temp->start - p->a_time;
		p = p->next;
	}
} // response_time

void calculate_waiting_tat( struct gantt_chart *c, struct process *p )
{
	while( p != NULL )
	{
		struct gantt_chart *temp = c;
		int t = 0;

		while( temp != NULL )
		{
			if( temp->process_id == p->pid )
				t = temp->end;	

			temp = temp->next;
		} // while

		p->tat = t - p->a_time;

		p->waiting_time = p->tat - p->cpu_burst;

		p = p->next;
	} // while
} // calculate_waiting_time


void average_time( struct process *h, int n)
{
	int r_t = 0, ta_t = 0, w_t = 0;
	float result = 0.0f;

	for(; h != NULL; h = h->next )
	{
		r_t += h->response_time;
		ta_t += h->tat;
		w_t += h->waiting_time;
	} // for

	result = ( r_t * 1.0f ) / n;
	printf("Average response time : %.2f\n", result );
	
	result = ( w_t * 1.0f ) / n;
	printf("Average waiting time : %.2f\n", result);
	
	result = ( ta_t * 1.0f ) / n;
	printf("Average turn around time : %.2f\n", result);
} //average_time

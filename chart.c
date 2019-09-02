#include<cstdio>
#include<cstdlib>
#include<iostream>
#include "common_type.h"
#include "extern_declaration.h"

void add_node_gantt_chart( int, int, int );
void print_gantt_chart( );


void add_node_gantt_chart( int s, int e, int p_id )
{
	struct gantt_chart *temp = ( struct gantt_chart *)( malloc( sizeof( struct gantt_chart )) );
	
	temp->start = s;
	temp->end = e;
	temp->process_id = p_id;
	temp->next = NULL;

	if( header == NULL )
		header = temp;
	else
		trailer->next = temp;

	trailer = temp;

} // add_node_gantt_chart


void print_gantt_chart( void  )
{
	struct gantt_chart *h = header;

	if( h == NULL )
		return;
	int temp = -1;
	for(; h != NULL ; h = h->next )
	{
		if( h->start != temp )
			printf("|%d|", h->start );

		printf("  P%-3d  |%d|", h->process_id, h->end);
		temp = h->end;
	} // for

	std::cout << std::endl;

}// print_gantt_chart

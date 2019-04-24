#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


int main( void )
{
	int pid, status;

	pid = fork();

	if ( pid )
	{
		printf("Child process\n");
		execl("~/test");
	} // child
	else{
		wait( &status );
		printf("Parent process\n");
	} // parent
	return 0;
}

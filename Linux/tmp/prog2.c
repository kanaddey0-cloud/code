#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("hello world\n");

	printf("I am %d before forking process\n", (int)getpid());

	pid_t pid = fork();

 	printf("Fork returned: %d\n", (int)pid);

	if(pid < 0)
	{
		perror("Fork failed");
	}
	else if(pid == 0)
	{
		printf("I am the child process pid %d\n", (int)getpid());
	}
	else
	{
		printf("I am the parent %d\n", (int)getpid());
	}
	
	return 0;
}

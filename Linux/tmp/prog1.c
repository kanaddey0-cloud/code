#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	printf("hello world\n");

	printf("I am %d before forking processs\n", (int)getpid());

	pid_t pid = fork();
	
	printf("fork returned: %d\n", (int)pid);

	return 0;
}

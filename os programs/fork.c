#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t x;

	x=fork();
	if(x==0)
		{
			printf("In Child X : %ld\n",(long)x);
			printf("In Child getppid()=%ld\n",(long)getppid());
		}
	else
	{
		printf("In Parent X : %ld\n",(long)x);
		printf("In Parent getppid()=%ld\n",(long)getppid());
	}
return 0;
}

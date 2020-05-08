#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{	
	int n = 0;
	pid_t pid; /*unique process identifier*/
	do
	{
		printf("Please enter a positive integer:"); 
		scanf("%d", &n);	
	}while (n <= 0); 
	/*Error checking to ensure that a positive integer is passed*/

	pid = fork();
	if (pid < 0) /* error occurred */
	{ 
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if (pid == 0) /* child process */
	{
		printf("Child process is working...\n");
		printf("%d", n);
		while (n != 1)
		{
			printf(", ");
			if (n%2 == 0) /* if n is even*/
				n = n/2;

			else /* if n is odd*/
				n = 3 * n + 1;

			printf("%d", n);
		}
		printf("\nChild process is done.\n");
	}
	else /* parent process */
	{
		printf("Parents is waiting for child process...\n");
		wait(NULL);
		printf("Parent process is done.\n");
	}
		
	return 0; 
}

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h> 		/* for O_CREAT, O_RDWR */

int main(){
	const char *shm_name = "Shared-memory";
	const int SIZE = 64;
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, 600);
	// shm_fd: shared memory file descriptor
	// O_CREAT: create if it does not yet exist
	// O_RDWR: now, open for reading and writing
	
	if(shm_fd == -1)
		printf("Error in shm_open"); 
		
	int ftrunc_res = ftruncate(shm_fd, SIZE);	// 64bytes(512 bits) is length of memory 
	// ftruncate(): configure the size of the shared-memory object (in bytes).
	
	if(ftrunc_res == -1)
		printf("Error in ftruncate");
		
	int *shm_ptr = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	// mmap(): map the memory-mapped file into memory.

	if(shm_ptr == MAP_FAILED)
		printf("Error in mmap");
			
	int n = 0;
	pid_t pid; /*unique process identifier*/
	do
	{
		printf("Please enter a positive integer:"); 
		scanf("%d", &n);	
		
	}while (n <= 0); 
	/*Error checking to ensure that a positive integer is passed*/
	
	pid = fork();
	if(pid < 0) /* error occurred */
	{
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	
	else if(pid == 0) /* child process */
	{ 
		printf("Child process is working...\n");
		shm_ptr[0] = n;
		int i = 1;
		while(n > 1)
		{
			if(n%2 == 0)
			{
				shm_ptr[i] = n/2;
				n = n/2;
				i++;
			}
			else
			{
				shm_ptr[i] = 3 * n + 1;
				n = 3 * n + 1;
				i++;
			}
		}
		shm_ptr[i] = -1; // mark the end
		printf("Child process is done.\n");
	}
	else /* parent process */
	{
		printf("Parents is waiting for child process...\n");
		wait(NULL);
		
		int i = 0;
		while(shm_ptr[i] != -1)
		{
			printf("%d",shm_ptr[i]);
			if(shm_ptr[i] != 1)
				printf(", ");
			i++;
		}
		int res = shm_unlink(shm_name);
		if(res == 0)
			printf("\nShared memory object is removed (unlinked) \n");
		else
			printf("Error while unlinking shared memory \n");
			
		printf("Parent process is done.\n");
	}
	return 0;
}

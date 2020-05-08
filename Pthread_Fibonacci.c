#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

long fib_arr[1000]; // this data is shared by the thread(s) 
void *fibonacci(void* params); // the thread 

 int main() {
	 
	int n = 0; //user input
	do
	{
		printf("Enter the number of Fibonacci numbers:"); 
		scanf("%d", &n);		
	}while (n <= 0); 

	pthread_t tid; // the thread identifier
	pthread_attr_t attr; // set of attributes for the thread
	pthread_attr_init(&attr); // get the default attributes

	pthread_create(&tid, &attr, fibonacci, (void*) &n); // create the thread
	pthread_join(tid, NULL); // waits for thread to finish

	//output fibonacci array after thread finishes.
	for(int i = 0; i <= n; i++) {
		printf("%ld ",fib_arr[i]);
	}
	return 0;
 }

void *fibonacci(void* params) {
	
	long fib0 = 0, fib1 = 1, next = 0;
	int total = *((int*) params);
	// first we cast params into (int*), and get the value out of it.
	//printf("\nTOTAL: %d\n", total);
	
	for (int i = 0 ; i <= total; i++ ) {
      if ( i <= 1 )
         next = i;
      else 
      {
         next = fib0 + fib1;
         fib0 = fib1;
         fib1 = next;
      }
	  fib_arr[i] = next; //store to shared_data array
	}
	pthread_exit(0); // Thread termination
}


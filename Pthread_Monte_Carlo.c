#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define THREADS_COUNT 8         //number of threads
#define TOT_COUNT 10000000      //total number of iterations

// points that occur in the circle store in a global variable
int circle_count = 0;

float randNumGen(){
  int random_value = rand(); //Generate a random number   
  float unit_random = random_value / (float) RAND_MAX; //make it between 0 and 1 
  return unit_random;
}

void *generate_points(void *unused)
{
  
  //get the total number of iterations for a thread
  float tot_iterations = TOT_COUNT / THREADS_COUNT;

  int counter = 0;

  for(counter = 0; counter < tot_iterations; counter++){
    float x = randNumGen();
    float y = randNumGen();

    float result = sqrt((x*x) + (y*y));

    if(result < 1)
    {
      //check if the generated value is inside a unit circle
      circle_count += 1;        
    }

  }
  pthread_exit(NULL);     
}

int main(int argc, char *argv[])
{
  pthread_t threads[THREADS_COUNT]; // the thread identifier, THREADS_COUNT of them

  int thread_return;
  long t; 

  for(t = 0; t < THREADS_COUNT; t++)
  {
    // If attr is NULL, then the thread is created with default attributes.
    thread_return = pthread_create(&threads[t], NULL, generate_points, NULL);
    if (thread_return)
    {
      printf("ERROR; return code from pthread_create() is %d\n", thread_return);
      exit(-1);
      /* On success, pthread_create() returns 0; on error, it returns an error
       number, and the contents of *thread are undefined. */
    }
  }

  //join the threads
  for(t = 0; t < THREADS_COUNT; t++){

    //The parent thread waits for child to complete.
    pthread_join(threads[t], NULL); 
  }
  printf("Value for Pi is %f \n", 4 * ((double)circle_count / TOT_COUNT));
  pthread_exit(NULL);
}

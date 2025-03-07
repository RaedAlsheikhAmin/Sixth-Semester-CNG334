#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
void *worker(void *param);

#define NUMBER_OF_DARTS		50000000

// to complete: variables



/*
 * Generates a double precision random number
 */
double random_double()
{
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {
	

	/* seed the random number generator */
          srandom((unsigned)time(NULL));

	// to complete: Threads Creations 


	/* estimate Pi */
	estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;

	printf("Pi = %f\n",estimated_pi);

	return 0;
}

void *worker(void *param)
{
	int number_of_darts;
	number_of_darts = *((int *)param);
	int i;
	int hit_count = 0;
	double x,y;

	for (i = 0; i < number_of_darts; i++) {

		/* generate random numbers between -1.0 and +1.0 (exclusive) */
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;

		if ( sqrt(x*x + y*y) < 1.0 )
			++hit_count;
	}


	
	circle_count += hit_count;


	pthread_exit(0);
}


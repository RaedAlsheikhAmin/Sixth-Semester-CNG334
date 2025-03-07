#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Name: Shayan Nadeem Bhutta
//Student ID: 2542413

typedef struct list
{
	int val;
	struct list *next;
} list;

void swap(int *lhs, int *rhs)
{
	int tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

void *readSort(void *arg) 
{
	int count = 0;
	int k = 0;
	char c;
	FILE *fileptr;
	char *filename = (char *) arg;
	
	fileptr = fopen(filename, "r");
	
	//This while block is used to calculate the number of lines in the file to define the array//
	while ((c = fgetc(fileptr)) != EOF)  
	{
		if (c == '\n') 
			count++;
	}
	
	int num[count];
	
	fileptr = fopen(filename, "r");
		
	while ( (fscanf(fileptr, "%d", &num[k])) != EOF )
	{
		k++;
	}
		
  int i;
  int j;
  	
  for (i = 0; i < count-1; i++)
  {
    int min = i;
    for (j = i+1; j < count; j++)
       if (num[j] < num[min]) min = j;
    	swap(&num[i], &num[min]);
  }
  
  list *head = malloc(sizeof(struct list));
  head->val = num[0];
  list *temp;
  list *tail;
  temp = malloc(sizeof(struct list));
  temp->val = num[1];
  head->next = temp;
  tail = temp;
  tail->next = NULL;	  
  
  for (i = 2; i < count; i++)
  {
  	temp = malloc(sizeof(struct list));
  	temp->val = num[i];
  	tail->next = temp;
  	tail = temp;
  	tail->next = NULL;
  }
  
  list *currptr = head;
  
printf("\nThread 1 is Sorting: ");
  
  while (currptr != NULL)
  {
  	printf("%d", currptr->val);
  	if (currptr->next != NULL)
  		printf("->");
  	currptr = currptr->next;
  	sleep(1);
  }
  
   pthread_exit(NULL);
  
}

void *readCheck(void *arg) 
{
	FILE *fileptr;
	char c;
	int count = 0;
	int i,j;
	int k = 0;
	char *filename = (char *) arg;
	
	fileptr = fopen(filename, "r");
	
	//This while block is used to calculate the number of lines in the file to define the array//
	while ((c = fgetc(fileptr)) != EOF)  
	{
		if (c == '\n') 
			count++;
	}
	
	int num[count];
	
	fileptr = fopen(filename, "r");
	
	while ( (fscanf(fileptr, "%d", &num[k])) != EOF )
	{
		k++;
	}
	
	for (i = 0; i < count-1; i++)
   {
    int min = i;
    for (j = i+1; j < count; j++)
       if (num[j] < num[min]) min = j;
    	swap(&num[i], &num[min]);
   }
  	
printf("\nThread 2 is Calculating Factorial: ");
  	
	  	for (k = 0; k < count; k++)
	{
		num[k] = factorial(num[k]);
		printf("%d", num[k]);
  			if ((k+1) != count)
  				printf(",");
		sleep(2);		  	
	}
	
   pthread_exit(NULL);
}

int factorial(int x)
{
	if (x == 0)
		return 1;
	else	
	    return (x * factorial(x-1)); 
}

int main() {
	
	char filename[50];
	
	printf("Please enter the file name:  ");
	scanf("%s", filename);
	
	pthread_t thread1;
	pthread_t thread2;

    pthread_create(&thread1, NULL, readSort, (void *) filename);
    pthread_create(&thread2, NULL, readCheck, (void *) filename);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

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

void readSort(char filename[]) 
{
	int count = 0;
	int k = 0;
	char c;
	FILE *fileptr;
	
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
  
  printf("Sorting: ");
  
  while (currptr != NULL)
  {
  	printf("%d", currptr->val);
  	if (currptr->next != NULL)
  		printf("->");
  	currptr = currptr->next;
  }
  
  printf("\n");
  
}

void readCheck(char filename[]) 
{
	FILE *fileptr;
	char c;
	int count = 0;
	int i,j;
	int k = 0;
	
	
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
  	
  	printf("Factorial: ");
  	
	  	for (k = 0; k < count; k++)
	{
		num[k] = factorial(num[k]);
		printf("%d", num[k]);
  			if ((k+1) != count)
  				printf(",");	
	}
	

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
	  
	readSort(filename);
	readCheck(filename);
	
	return 0;
}

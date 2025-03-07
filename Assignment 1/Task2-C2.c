//Raed Alsheikh Amin 2528271

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

// structure to represent a process that will be used in this code
 struct Process {
    int id; // process ID
    int arrival_time; // arrival time of the process
    int execution_time; // execution time of the process
    int priority; // priority of the process
};
typedef struct Process processes;//for easier usability



void initializeProcesses(processes *queue, int size) {

    srand(time(NULL));
    int i = 0;

    //initializing the carray
    for (i ; i < size; i++) {
        queue[i].id = i + 1;// initializing the process id
        queue[i].arrival_time = 0;//assuming all arrived at time 0
        queue[i].execution_time = (rand() % 21) + 10; // [10, 30]
        queue[i].priority = (rand() % 10) + 1; // [1, 10]
    }
}

// function to sort processes by execution time using selection sort
void sortByExecutionTime(processes *queue, int size) {
    int i = 1;
    for (i; i < size; i++) {
        processes key = queue[i];
        int j = i - 1;

        // Move elements greater than key to one position ahead
        while (j >= 0 && key.execution_time < queue[j].execution_time) {
            queue[j + 1] = queue[j];
            j--;
        }
        queue[j + 1] = key;
    }
}


// function to sort processes by priority using selection sort
void sortByPriority(processes *queue, int size) {
    int i = 0;
    for (i; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (queue[j].priority < queue[min_index].priority) {
                min_index = j;
            }
        }

        // swap the minimum priority process with the current process
        processes temp = queue[min_index];
        queue[min_index] = queue[i];
        queue[i] = temp;
    }
}

// function to sort processes
void sortProcesses(processes *queue) {
    // generate a random number to determine sorting criteria
    srand(time(NULL));
  int sortingCriteria = rand() % 2;
  int size=6;
    if (sortingCriteria == 0) {
        printf("Sorting by execution time:\n");
        int i = 1;
        for (i; i < size; i++) {
            processes key = queue[i];
            int j = i - 1;
            // move elements greater than key to one position ahead
            while (j >= 0 && key.execution_time < queue[j].execution_time) {
                queue[j + 1] = queue[j];
                j--;
            }
            queue[j + 1] = key;
        }
    } else {
        printf("Sorting by priority:\n");
        int i = 0;
        int j;
        for (i; i < size - 1; i++) {
            int min_index = i;
            for (j = i + 1; j < size; j++) {
                if (queue[j].priority < queue[min_index].priority) {
                    min_index = j;
                }
            }

            // Swap the minimum priority process with the current process
            processes temp = queue[min_index];
            queue[min_index] = queue[i];
            queue[i] = temp;
        }
    }
    // Print sorted processes
    int i = 0;
    for (i ; i < 6; i++) {
        printf("Process %d: Arrival Time = %d, Execution Time = %d, Priority = %d\n",
               queue[i].id, queue[i].arrival_time, queue[i].execution_time, queue[i].priority);
    }
}

// Function to execute processes using non-preemptive priority scheduling
/*
implements non-preemptive priority scheduling for executing processes.
It initializes variables to track the current time, the number of completed processes,
and the index of the currently running process. Inside the while loop,
it iterates until all processes are completed. Within each iteration,
it searches for the process with the highest priority among those that have arrived and are not yet completed.
If such a process is found, it is executed by decrementing its execution time.
The function then updates the current time and prints the details of the running process.
If the process finishes execution (execution time becomes 0),
it increments the count of completed processes and resets the running process index.
This process continues until all processes are completed.
*/
void executeProcesses_priority(processes *queue) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int running = -1; // Index of the currently running process

    int size=6;
    while (completed < size) {
        // Find the process with the highest priority among the processes that have arrived
        int highest_priority = 100; // Initialize with a priority higher than any possible process
        int highest_priority_index = -1;
        int i = 0;
        for (i; i < size; i++) {
            if (queue[i].arrival_time <= time && queue[i].priority < highest_priority && queue[i].execution_time > 0) {
                highest_priority = queue[i].priority;
                highest_priority_index = i;
            }
        }

        // If no process is available, increment time and continue
        if (highest_priority_index == -1) {
            time++;
            continue;
        }

        // Execute the process with the highest priority
        running = highest_priority_index;
        queue[running].execution_time--;
        time++;

        // Print the currently running process
        printf("Time %d: Process %d is running (Priority: %d, Remaining Time: %d)\n",
               time, queue[running].id, queue[running].priority, queue[running].execution_time);

        // If the process has finished execution, mark it as completed
        if (queue[running].execution_time == 0) {
            completed++;
            running = -1;
        }
    }
}

// Function to execute processes using shortest process next scheduling
/*
implements shortest job next scheduling for executing processes.
It initializes variables to track the current time, the number of completed processes,
and the index of the currently running process. Within a while loop,
the function iterates until all processes are completed.
Inside each iteration, it searches for the process with the shortest remaining execution time among those that have arrived and are not yet completed.
If such a process is found, it is executed by decrementing its execution time.
The function then updates the current time and prints the details of the running process.
If the process finishes execution (execution time becomes 0),
it increments the count of completed processes and resets the running process index. T
his process continues until all processes are completed.
*/
void executeProcesses_shortest(processes *queue) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int running = -1; // Index of the currently running process
    int size=6;

    while (completed < size) {
        // Find the process with the shortest remaining execution time among the processes that have arrived
        int shortest_time = 999; // Initialize with a time longer than any possible process
        int shortest_time_index = -1;
        int i = 0;
        for (i; i < size; i++) {
            if (queue[i].arrival_time <= time && queue[i].execution_time < shortest_time && queue[i].execution_time > 0) {
                shortest_time = queue[i].execution_time;
                shortest_time_index = i;
            }
        }

        // If no process is available, increment time and continue
        if (shortest_time_index == -1) {
            time++;
            continue;
        }

        // Execute the process with the shortest remaining time
        running = shortest_time_index;
        queue[running].execution_time--;
        time++;

        // Print the currently running process
        printf("Time %d: Process %d is running (Remaining Time: %d)\n",
               time, queue[running].id, queue[running].execution_time);

        // If the process has finished execution, mark it as completed
        if (queue[running].execution_time == 0) {
            completed++;
            running = -1;
        }
    }
}

// Function to execute processes based on the sorting criteria, it will choose which scheduling to perform based on the random generated number in the main
//which we sorted according to it

void executeProcesses(processes *queue, int size, int sortingCriteria) {
    if (sortingCriteria == 0) {
      printf("Executing processes using shortest process next scheduling:\n");
      executeProcesses_shortest(queue);

    } else {
      printf("Executing processes using non-preemptive priority scheduling:\n");
      executeProcesses_priority(queue);

    }
}



int main() {
  processes queue[6];
  initializeProcesses(queue, 6);
  int i = 0;
  printf("Before sorting!\n");
    for (i ; i < 6; i++) {//printing the processes before sorting them
        printf("Process %d: Arrival Time = %d, Execution Time = %d, Priority = %d\n",
               queue[i].id, queue[i].arrival_time, queue[i].execution_time, queue[i].priority);
    }



// Create two threads to execute sortProcesses and executeProcesses
  pthread_t sort_thread, exec_thread;

  // Create the sort_thread, passing the queue array as an argument
  int sort_thread_create_result = pthread_create(&sort_thread, NULL, sortProcesses, queue);
  // Check if the sort_thread was created successfully
  if (sort_thread_create_result != 0) {
    printf("Error creating sort_thread: %d\n", sort_thread_create_result);
    return 1; // Exit the program with an error code
  }

  // Create the exec_thread, passing the queue array as an argument
  int exec_thread_create_result = pthread_create(&exec_thread, NULL, executeProcesses, queue);
  // Check if the exec_thread was created successfully
  if (exec_thread_create_result != 0) {
    printf("Error creating exec_thread: %d\n", exec_thread_create_result);
    return 1; // Exit the program with an error code
  }

  // Join the sort_thread to wait for its completion
  int sort_thread_join_result = pthread_join(sort_thread, NULL);
  // Check if joining the sort_thread was successful
  if (sort_thread_join_result != 0) {
    printf("Error joining sort_thread: %d\n", sort_thread_join_result);
    return 1; // Exit the program with an error code
  }

  // Join the exec_thread to wait for its completion
  int exec_thread_join_result = pthread_join(exec_thread, NULL);
  // Check if joining the exec_thread was successful
  if (exec_thread_join_result != 0) {
    printf("Error joining exec_thread: %d\n", exec_thread_join_result);
    return 1; // Exit the program with an error code
  }

  return 0;
}

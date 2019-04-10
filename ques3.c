/*
Ques. 3. Consider a scheduler which schedules the job by considering the arrival time of the processes where arrival time if given as 0 is discarded or displayed as error. The scheduler implements the shortest job first scheduling policy, but checks the queue of the processes after the every process terminates and time taken for checking and arranging the process according to the shortest job is 2 time unit. Compute the waiting time, turnaround time and average waiting time and turnaround time of the processes. Also compute the total time taken by the processor to compute all the jobs.

The inputs for the number of requirements, arrival time and burst time should be provided by the user.

Consider the following units for reference.
Process    Arrival time    Burst Time
1   		 0   		 6
2    		3   		 2
3    		5   		 1
4    		9   		 7
5    		10   		 5
6    		12    		3
7   		 14   		 4
8    		16    		5
9    		17    		7
10    		19    		2
Develop a scheduler which submits the processes to the processor in the defined scenario, and compute the scheduler performance by providing the waiting time for process, turnaround time for process and average waiting time and turnaround time.

*/


#include<conio.h>
#include<stdio.h>
#define INT_MAX  2147483647;

struct Process { 
	int pid; // Process ID 
	int bt; // Burst Time 
	int art; // Arrival Time 
}; 

// Function to find the waiting time for all 
// processes 
void findWaitingTime(struct Process proc[], int n, int wt[]) 
{ 
	int rt[n],i,j; 

	// Copy the burst time into rt[] 
	for (i = 0; i < n; i++) 
		rt[i] = proc[i].bt; 

	int complete = 0, t = 0, minm = INT_MAX; 
	int shortest = 0, finish_time; 
	int  check = 0; 

	// Process until all processes gets 
	// completed 
	while (complete != n) { 

		// Find process with minimum 
		// remaining time among the 
		// processes that arrives till the 
		// current time` 
		for (j = 0; j < n; j++) { 
			if ((proc[j].art <= t) && 
			(rt[j] < minm) && rt[j] > 0) { 
				minm = rt[j]; 
				shortest = j; 
				check = 1; 
			} 
		} 

		if (check == 0) { 
			t++; 
			continue; 
		} 

		// Reduce remaining time by one 
		rt[shortest]--; 

		// Update minimum 
		minm = rt[shortest]; 
		if (minm == 0) 
			minm = INT_MAX; 

		// If a process gets completely 
		// executed 
		if (rt[shortest] == 0) { 

			// Increment complete 
			complete++; 
			check = 0; 

			// Find finish time of current 
			// process 
			finish_time = t + 1; 

			// Calculate waiting time 
			wt[shortest] = finish_time - 
						proc[shortest].bt - 
						proc[shortest].art; 

			if (wt[shortest] < 0) 
				wt[shortest] = 0; 
		} 
		// Increment time 
		t++; 
	} 
} 

// Function to calculate turn around time 
void findTurnAroundTime(struct Process proc[], int n, 
						int wt[], int tat[]) 
{ 
    int i;
	// calculating turnaround time by adding 
	// bt[i] + wt[i] 
	for (i = 0; i < n; i++) 
		tat[i] = proc[i].bt + wt[i]; 
} 

// Function to calculate average time 
void findavgTime(struct Process proc[], int n) 
{ 
	int wt[n], tat[n], total_wt = 0, total_tat = 0; 

	// Function to find waiting time of all 
	// processes 
	findWaitingTime(proc, n, wt); 

	// Function to find turn around time for 
	// all processes 
	findTurnAroundTime(proc, n, wt, tat); 

	// Display processes along with all 
	// details 
	printf("Processes   Burst time  Waiting time  Turn around time\n");

	// Calculate total waiting time and 
	// total turnaround time
	int i; 
	for (i = 0; i < n; i++) { 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		printf("  %d \t\t %d \t\t %d \t\t %d \n",proc[i].pid,proc[i].bt,wt[i],tat[i]);
	} 
    printf("\nAverage waiting time =  %f",(float)total_wt / (float)n);
    printf("\nAverage turn around time =  %f",(float)total_tat / (float)n);
    
} 

// Driver code 
int main() 
{ 
	/*Process proc[] = { { 1, 6, 1 }, { 2, 8, 1 }, 
					{ 3, 7, 2 }, { 4, 3, 3 } }; */
					
	int n;
					
	int choice;   
	printf("===menu====\n");
	printf("1.Give value by user.\n");
	printf("2.Check program with default values.\n");
	printf("Enter your choice : ");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1 : {
		        printf("Enter no. of process :  ");
	            scanf("%d",&n);
	            struct Process p[n];
	            int i;
	            for(i=0;i<n;i++)
	            {   p[i].pid=i+1;
	            	printf("Enter Arrival time for process[%d] : " ,i+1);
	            	scanf("%d",&p[i].art);
	            	printf("Enter Worst time for process[%d] : " ,i+1);
	            	scanf("%d",&p[i].bt);
	            	printf("\n\n");
	            }
	            findavgTime(p,n); 
	            break;
				}
	            
	    case 2 : {
	            n=10;
	            struct Process p[] = {{1,1,6}, {2,3,2}, {3,5,1}, {4,9,7}, 
				             {5,10,5},{6,12,3}, {7,14,4}, 
							 {8,16,5}, {9,17,7}, {10,19,2}};
							 	
				findavgTime(p, n); 
	            break;
	        }
	    default : 
	        printf("Wrong choice entered . ");
		        
	}

					
	//int n = sizeof(proc) / sizeof(proc[0]); 


	return 0; 
} 



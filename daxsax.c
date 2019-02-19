
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 
  
int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int phnum) 
{ 
    if (state[phnum] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
        // state that eating 
        state[phnum] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      phnum + 1, LEFT + 1, phnum + 1); 
  
        printf("Philosopher %d is Eating\n", phnum + 1); 
  
        // sem_post(&S[phnum]) has no effect 
        // during takefork 
        // used to wake up hungry philosophers 
        // during putfork 
        sem_post(&S[phnum]); 
    } 
} 
  
// take up chopsticks 
void take_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // state that hungry 
    state[phnum] = HUNGRY; 
  
    printf("Philosopher %d is Hungry\n", phnum + 1); 
  
    // eat if neighbours are not eating 
    test(phnum); 
  
    sem_post(&mutex); 
  
    // if unable to eat wait to be signalled 
    sem_wait(&S[phnum]); 
  
    sleep(1); 
} 
  
// put down chopsticks 
void put_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[phnum] = THINKING; 
  
    printf("Philosopher %d putting fork %d and %d down\n", 
           phnum + 1, LEFT + 1, phnum + 1); 
    printf("Philosopher %d is thinking\n", phnum + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++) 
  
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++) { 
  
        // create philosopher processes 
        pthread_create(&thread_id[i], NULL, 
                       philospher, &phil[i]); 
  
        printf("Philosopher %d is thinking\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL); 
} 


#include<stdio.h>
#include<stdlib.h>

struct process
{
	int at,bt,ct,wt,tat,p;
}process[10];

struct process temp;
void main()
{
int number,i,j;

	printf("enter the number process\n");
   scanf("%d",&number);

printf("enter arrival and burst time\n");
for(i=0;i<number;i++)
{
 printf("p[%d]:",i+1);
 scanf("%d%d",&process[i].at,&process[i].bt);
 process[i].p=i+1;

}
for(i=0;i<number-1;i++)
{
  for(j=i;j<number;j++)
   {
   	if(process[i].at>process[j].at)
     {
     	temp=process[i];
     	process[i]=process[j];
     	process[j]=temp;
     }
   }
}

process[0].ct=process[0].bt+process[0].at;
int time=process[0].ct;
process[0].tat=process[0].bt;
if(time>0)
{
	printf("process aws idle for 0 to %d",process[0].at);
}
for(i=1;i<number;i++)
{

if(process[i].at>time)
{
	process[i].ct=process[i].bt+process[i].at;
   printf("process idle for%d to %d \n",time,process[i].ct-1);
	
	time=process[i].ct;
	process[i].tat=time-process[i].at;
	process[i].wt=time-process[i].at-process[i].bt;
	
}
else
{
    process[i].ct=time+process[i].bt;
	time=process[i].ct;
	process[i].tat=time-process[i].at;
	process[i].wt=time-process[i].at-process[i].bt;
	   

}


}

printf("process\t\tat\tbt\twt\ttat\tct\n");
for(i=0;i<number;i++)
{
	printf("%d\t\t%d\t%d\t%d\t%d\t%d\t\n",process[i].p,process[i].at,process[i].bt,process[i].wt,process[i].tat,process[i].ct);
}

}

#include<stdio.h>
#include<fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	int fd_dup,fd,op;
	int return_value;
	char name[100], *read_data, *write_data;
	do
	{
		printf("\nThe calls: \n");
		printf("1. Creat\n");
		printf("2. Open\n");
		printf("3. Close\n");
		printf("4. Read\n");
		printf("5. Write\n");
		printf("6. Lseek\n");
		printf("7. Duplicate\n");
		printf("8. Link\n");
		printf("9. Unlink\n");
		printf("Enter the option: ");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1 ://Creating a File
				printf("Enter the name of the file: ");
				scanf("%s",name);
			   	fd = creat(name, S_IRWXU);
				printf("\n the file is created");
				printf("%d",fd);
				break;

			case 2 ://Opening a File
				printf("Enter the file name to be opened :");
				scanf("%s", name);
				fd = open(name, O_CREAT || O_RDWR);
				printf("%d",fd);
				break;

			case 3: //Closing the file that was opened in case 2
				return_value = close(fd); // return success
				if( return_value == 0)
					printf("\n File successfully closed");
				else if( return_value == -1)
					printf("\n File closure error.");
				break;

			case 4: //Reading from a file
				read_data = (char*)malloc(sizeof(char) * 100);
				printf("Enter the file name to be read :");
				scanf("%s",name);
				fd = open(name,  O_RDONLY);
				return_value = read(fd, read_data, 4); // fd, buf, count
				if( return_value == -1)
					printf("Error in reading");
				else
				{	read_data[return_value] = '\0'; 
					printf("The 4 characters read are: %s",read_data);
				}
				break;

			case 5: //Writing into the file
				write_data = (char*)malloc(100);
				printf("Enter the file to which the data is to be written: ");
				scanf("%s",name);
				fd = creat(name,  S_IRWXU);
				printf("Enter the data to be written: ");		
				scanf("%s",write_data);
				return_value = write(fd, write_data, strlen(write_data));
				if( return_value != -1 )
					printf("Data is written into the file");
				else
					printf("Error in writing data");
				close(fd);
				break;				

			case 6: //Lseek
				return_value = lseek(fd, 2, SEEK_SET); 	
				if(return_value == -1)
					printf("\n Error");
				else
					printf("\n The offset position: %d",return_value);
					//printf("The data at seek position :")
				break;
			case 7: // Creating dup fd
				fd_dup = dup(fd);
				printf("\nFile descriptor duplicated");
				break;
			case 8: //Link
				link("asdfgh","newname");
				break;
			case 10: //Unlink
				unlink("asdfgh");
				break;
				

				
				
		}
	}while(op != 10);
}

#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#define bs 5
pthread_mutex_t empty,full;
pthread_t tid;
int readcount;

void intialize()
{
    pthread_mutex_init(&empty,NULL);
    pthread_mutex_init(&full,NULL);
    readcount=0;
}

void * reader (void * param)
{
    int waittime;
    waittime = rand() % bs;
    printf("\nReader is trying to enter");
    pthread_mutex_lock(&empty);
    readcount++;
    if(readcount==1)
        pthread_mutex_lock(&full);
    printf("\n%d Reader is inside ",readcount);
    pthread_mutex_unlock(&empty);
    sleep(waittime);
    pthread_mutex_lock(&empty);
    readcount--;
    if(readcount==0)
        pthread_mutex_unlock(&full);
    pthread_mutex_unlock(&empty);
    printf("\nReader is Leaving");
}   

void * writer (void * param)
{
    int waittime;
    waittime=rand() % bs;
    printf("\nWriter is trying to enter");
    pthread_mutex_lock(&full);
    printf("\nWrite has entered");
    sleep(waittime);
    pthread_mutex_unlock(&full);    
    printf("\nWriter is leaving");
    sleep(30);
    exit(0);
}

int main()
{
    int n1,n2,i;    
    printf("\nEnter the no of readers: ");
    scanf("%d",&n1);
    printf("\nEnter the no of writers: ");
    scanf("%d",&n2);
    for(i=0;i<n1;i++)
        pthread_create(&tid,NULL,reader,NULL);  
    for(i=0;i<n2;i++)
        pthread_create(&tid,NULL,writer,NULL);
    sleep(30);
    exit(0);
}

#include<stdio.h>

struct process
{
      char process_name;
      int at, bt, ct, wt, tat, priority;
      int status;
}process_queue[10];

int limit;

void Arrival_Time_Sorting()
{
      struct process temp;
      int i, j;
      for(i = 0; i < limit - 1; i++)
      {
            for(j = i + 1; j < limit; j++)
            {
                  if(process_queue[i].at > process_queue[j].at)
                  {
                        temp = process_queue[i];
                        process_queue[i] = process_queue[j];
                        process_queue[j] = temp;
                  }
            }
      }
}

void main()
{
      int i, time = 0, bt = 0, largest;
      char c;
      float wt = 0, tat = 0, avwt, avtat;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      for(i = 0, c = 'A'; i < limit; i++, c++)
      {
            process_queue[i].process_name = c;
            printf("\nEnter Details For Process[%C]:\n", process_queue[i].process_name);
            printf("Enter Arrival Time:\t");
            scanf("%d", &process_queue[i].at );
            printf("Enter Burst Time:\t");
            scanf("%d", &process_queue[i].bt);
            printf("Enter Priority:\t");
            scanf("%d", &process_queue[i].priority);
            process_queue[i].status = 0;
            bt = bt + process_queue[i].bt;
      }
      Arrival_Time_Sorting();


      
      process_queue[9].priority = -9999;
      printf("\nProcess Name\tArrival Time\tBurst Time\tPriority\tWaiting Time\tcompletion time\t");
      for(time = process_queue[0].at; time < bt;)
      {
            largest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(process_queue[i].at <= time && process_queue[i].status != 1 && process_queue[i].priority > process_queue[largest].priority)
                  {
                        largest = i;
                  }
            }
            time = time + process_queue[largest].bt;
            process_queue[largest].ct = time;
            process_queue[largest].wt = process_queue[largest].ct - process_queue[largest].at - process_queue[largest].bt;
            process_queue[largest].tat = process_queue[largest].ct - process_queue[largest].at;
            process_queue[largest].status = 1;
            wt = wt + process_queue[largest].wt;
            tat = tat + process_queue[largest].tat;
            printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", process_queue[largest].process_name, process_queue[largest].at,process_queue[largest].bt,process_queue[largest].priority, process_queue[largest].wt,process_queue[largest].tat,process_queue[largest].ct);
      }
      avwt = wt / limit;
      avtat = tat / limit;
      printf("\n\nAverage waiting time:\t%f\n", avwt);
      printf("Average Turnaround Time:\t%f\n", avtat);
}
#include<stdio.h>
struct process{
	int pid,at,visited,bt,ct,tat,wt,priority;
};

void main()
{
	int i =0, n,j;
	int time=0;

	printf("Enter number of processes: \n");
	scanf("%d", &n);

	struct process p[10];
	while(i<n)
	{
		p[i].visited = 0;                                 //visited status
		p[i].pid = i;
		printf(" the arrival time of %d process: \n", i );
		scanf("%d", &p[i].at);
		printf("Enter burst time of %d process \n:", i);
		scanf("%d",&p[i].bt);
		printf("Enter priority");
		scanf("%d",&p[i].priority);
		i++;
	}
  int quantam;
	printf("enter priority\n");
	scanf("%d",&quantam);

	struct process temp;
	for(i=0;i<n;i++)                        //sorting by arrival time
	{	for ( j = 0; j<n-1;j++)
		{
			if(p[j].at > p[j+1].at)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}

	int temp_bt[10];                         //saving burst time in temp array
	i = 0;
	while(i<n)
	{
		temp_bt[i] = p[i].bt;
		i++;
	}
	

	int count = 0;
	int flag = 1;
	i=0;
	while(flag)
	{	
		int j;
		int small_index=-1;
		struct process small;  //new process
		small.priority=-999;
		for(j=0;j<n;j++)
		{
			if(p[j].at <= time && p[j].visited == 0)
			{	
				if(p[j].priority>small.priority)
				{
					small_index = j;                   // process id saving
					small = p[j];                  //saving data of smallest burst time in process(small)
				}
			}
			
		}
		if(small_index==-1)            //no process found condition or idle case in between
		{
			for(i=0;i<n;i++)
			{
				if(p[i].at>time && p[i].visited==0)
				{
					small_index=i;
					break;
				}
			}
		}
		i = small_index;         //process with least burst time found

						if(p[i].at > time)              //idle case
						 {
							printf("The process was idle from %d to %d\n",time,p[i].at );            //if this condition works else wont  work
							                                                                             // goes to while loop
							time  = p[i].at;
							
						 }
						else
						{	if(p[i].bt<=quantam)
							{
								time=time+p[i].bt;
                                p[i].bt=0;

							}
							else
							{
								p[i].bt=p[i].bt-quantam;
								time=time+quantam;
							}
						
								
							if (p[i].bt == 0)
							{
								
								p[i].visited =1;	
								p[i].ct = time;
								p[i].tat = p[i].ct - p[i].at;
								p[i].wt = p[i].tat - temp_bt[i];
							}
								
						}

		int k,count=0;

		for (k = 0; k < n; ++k)
			if ( p[k].visited == 1)	
				count++;
		if (count == n)
			flag = 0;

	}


	printf("pid 	A.T 	B.T 	C.T 	T.A.T 	W.T\n");
	int avg_tat=0,avg_ct=0,avg_wt=0;
	for ( i = 0; i < n; ++i)
	{
			printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, temp_bt[i],p[i].ct,p[i].tat,p[i].wt);
			avg_tat+=p[i].tat;
			avg_ct+=p[i].ct;
			avg_wt+=p[i].wt;
	}

	printf("\nThe average C.T: %f\n",(float)(avg_ct/(float)n));
	printf("The average T.A.T: %f\n",(float)(avg_tat/(float)n));
	printf("The average W.T: %f\n",(float)(avg_wt/(float)n));
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

struct process
{
	int process_id;
	int arrival_time;
	int burst_time;
	int completion_time;
	int waiting_time;
	int turn_around_time;
	int remaining_time;
};

int queue[N];
int front = 0, rear = 0;
struct process proc[N];

void enqueue(int process_id)
{
	queue[rear] = process_id;
	rear = (rear+1)%N;
}

int dequeue()
{
	if(front == rear)
		return -1;

	int return_position = queue[front];
	front = (front +1)%N;
	return return_position;
}

int main()
{
	float wait_time_total = 0.0, tat = 0.0, avg_ct = 0.0;
	int n,time_quantum;
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	//input
	for(int i=0; i<n; i++)
	{
		printf("Enter the arrival time for the process%d: ",i+1);
		scanf("%d", &proc[i].arrival_time);
		printf("Enter the burst time for the process%d: ",i+1);
		scanf("%d", &proc[i].burst_time);
		proc[i].process_id = i+1;
		proc[i].remaining_time = proc[i].burst_time;
	
	}

	printf("Enter time quantum: ");             //time quantum
	scanf("%d",&time_quantum);

	int time=0; 
	int processes_left=n;   
	int position=-1; 		
	int local_time=0; 

	//enqueuing all arrived elements arrvied at time=0
	for(int j=0; j<n; j++)
	{
		if(proc[j].arrival_time == time)
			enqueue(j);
	}

	while(processes_left)
	{
		if(local_time == 0) 
		{
			if(position != -1)
				enqueue(position);

			position = dequeue();            
		}

		for(int i=0; i<n; i++)
		{
			if(proc[i].arrival_time > time)
				continue;
			if(i==position)
				continue;
			if(proc[i].remaining_time == 0)
				continue;

			proc[i].waiting_time++;
			proc[i].turn_around_time++;
		}

		if(position != -1)
		{
			proc[position].remaining_time--;
			proc[position].turn_around_time++;
			
			if(proc[position].remaining_time == 0)
			{
				processes_left--;
				local_time = -1;
				position = -1;
			}
		}
		else
			local_time = -1; 

		time++;
		local_time = (local_time +1)%time_quantum;
		for(int j=0; j<n; j++)
			if(proc[j].arrival_time == time)	
				enqueue(j);
	}

	printf("\n");

	//to calculate ct
	for (int i = 0; i < n; ++i)
	{
		proc[i].completion_time = proc[i].turn_around_time + proc[i].arrival_time;
	}

	printf("Process\t\tArrival Time\tBurst Time\tCompletion Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", proc[i].process_id, proc[i].arrival_time);
		printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].burst_time,proc[i].completion_time, proc[i].waiting_time, proc[i].turn_around_time);

		tat += proc[i].turn_around_time;
		wait_time_total += proc[i].waiting_time;
		avg_ct += proc[i].completion_time;
	}

	tat = tat/(1.0*n);
	wait_time_total = wait_time_total/(1.0*n);
	avg_ct /= n;
	printf("\nAverage completion time     : %f",avg_ct);
	printf("\nAverage waiting time     : %f",wait_time_total);
	printf("\nAverage turn around time : %f\n", tat);
	
}



 //          working
#include<stdio.h>
#include<stdlib.h>

struct process
{
	int at,bt,ct,wt,tat,p;
}process[10];

struct process temp;
void main()
{
int number,i,j,min;

	printf("enter the number process\n");
   scanf("%d",&number);

printf("enter arrival and burst time\n");
for(i=0;i<number;i++)
{
 printf("p[%d]:",i+1);
 scanf("%d%d",&process[i].at,&process[i].bt);
 process[i].p=i+1;

}
for(i=0;i<number-1;i++)
{
  for(j=i;j<number;j++)
   {
   	if(process[i].at>process[j].at)
     {
     	temp=process[i];
     	process[i]=process[j];
     	process[j]=temp;
     }
     if(process[i].at==process[j].at)// if same burst time
     {
              if(process[i].bt>process[j].bt) 
              {
              	temp=process[i];
     	        process[i]=process[j];
               	process[j]=temp;
              }

     }
   }
}


// code above same as fcfs

process[0].ct=process[0].at+process[0].bt; //fitst process in  line
process[0].tat=process[0].bt;
 	printf("process in order %d\n",process[0].p );
int time=process[0].ct;
if(time>0)
{
	printf("process ide ffor 0 to %d\n",time-1);
}

for(i=1;i<number;i++)
{
       if(process[i].at>time)
       {
       	process[i].ct=process[i].at+process[i].bt;
       	printf("cpu was idle for %d to %d\n",time,process[i].ct-1);
       	time=process[i].ct;
       	process[i].wt=0;
       	process[i].tat=process[i].bt;
       	printf("process in order%d\n",process[i].p );

       }
        else
        {
		         min=process[i].bt;
		                 //
		         for(j=i;j<number;j++)           //SWAPPING two process
		         {
		     	 if(process[j].at<=time&&process[j].bt<min)
		     	 {
		     	 	min=process[j].bt;
		     		temp=process[i];
		         	process[i]=process[j];
		     	    process[j]=temp;
		     	   // printf("swapping %d %d \n",i+1,j+1);

		       	  }
		         }
		         printf("process in order %d\n",process[i].p );
		         process[i].ct=time+process[i].bt;
		         time=process[i].ct;
		         process[i].tat=time-process[i].at;
		         process[i].wt=time-process[i].at-process[i].bt;
          }

}



//final answers printing

printf("process\t\tat\tbt\twt\ttat\tct\n");
for(i=0;i<number;i++)
{
	printf("%d\t\t%d\t%d\t%d\t%d\t%d\t\n",process[i].p,process[i].at,process[i].bt,process[i].wt,process[i].tat,process[i].ct);
}

}

#include<stdio.h>
#include<stdlib.h>
 
int mutex=1,full=0,empty=3,x=0;
 
int main()
{
	int n;
	void producer();
	void consumer();
	int wait(int);
	int signal(int);
	printf("\n1.Producer\n2.Consumer\n3.Exit");
	while(1)
	{
		printf("\nEnter your choice:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:	if((mutex==1)&&(empty!=0))
						producer();
					else
						printf("Buffer is full!!");
					break;
			case 2:	if((mutex==1)&&(full!=0))
						consumer();
					else
						printf("Buffer is empty!!");
					break;
			case 3:
					exit(0);
					break;
		}
	}
	
	return 0;
}
 
int wait(int s)
{
	return (--s);
}
 
int signal(int s)
{
	return(++s);
}
 
void producer()
{
	mutex=wait(mutex);
	full=signal(full);
	empty=wait(empty);
	x++;
	printf("\nProducer produces the item %d",x);
	mutex=signal(mutex);
}
 
void consumer()
{
	mutex=wait(mutex);
	full=wait(full);
	empty=signal(empty);
	printf("\nConsumer consumes item %d",x);
	x--;
	mutex=signal(mutex);
}
#include<stdio.h>
struct process
{
	int pid,at,visited,bt,ct,tat,wt;
};

void main()
{
	int i =0, n,j;
	int time=0;

	printf("Enter number of processes: \n");
	scanf("%d", &n);

	struct process p[10];
	while(i<n)
	{
		p[i].visited = 0;                                 //visited status
		p[i].pid = i+1;
		printf(" the arrival time of %d process: \n", i+1 );
		scanf("%d", &p[i].at);
		printf("Enter burst time of %d process \n:", i+1);
		scanf("%d",&p[i].bt);
		i++;
	}
	struct process temp;
	for(i=0;i<n;i++)                        //sorting by arrival time
	{	for ( j = 0; j<n-1;j++)
		{
			if(p[j].at > p[j+1].at)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}

     int temp_bt[10];
	for(i=0;i<n;i++)

        temp_bt[i]=p[i].bt;


int flag=1;
int count=0;
   while(flag)
       {
          struct process min;
          min.bt=9999;
          int small_index=-1;
          for(i=n-1;i>=0;i--)
          {
            if(p[i].at<=time&&p[i].visited==0&&p[i].bt<=min.bt)
               {
                    min=p[i];
                    small_index=i;
                  
               }
           }

          

         if(small_index==-1)        //idle case
         {
           for(i=0;i<n;i++)
           {
                 if(p[i].visited==0&&p[i].at>time)
                 {
                 	small_index=i;
                   break;
                 }
           }
          }

           i=small_index;



          if(p[i].at>time)
          {

             printf("process was idle for %d  %d\n",time,p[i].at );
             time=p[i].at;
          }
          else
          {
           p[i].bt--;
           time++;

           if(p[i].bt==0)
           {
           	p[i].visited=1;
           	p[i].ct=time;
           	p[i].tat=p[i].ct-p[i].at;
           	p[i].wt=p[i].tat-temp_bt[i];
           }

           
          }

        int count=0;
        for(i=0;i<n;i++)
        {
        	if(p[i].visited==1)
        		count++;

        }
          if(count==n)
          	flag=0;
         

       }//while

       printf("pid 	A.T 	B.T 	C.T 	T.A.T 	W.T\n");
	int avg_tat=0,avg_ct=0,avg_wt=0;
	for ( i = 0; i < n; ++i)
	{
			printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, temp_bt[i],p[i].ct,p[i].tat,p[i].wt);
			avg_tat+=p[i].tat;
			avg_ct+=p[i].ct;
			avg_wt+=p[i].wt;
	}

	printf("\nThe average C.T: %f\n",(float)(avg_ct/(float)n));
	printf("The average T.A.T: %f\n",(float)(avg_tat/(float)n));
	printf("The average W.T: %f\n",(float)(avg_wt/(float)n));
}



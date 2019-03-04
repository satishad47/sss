#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>
int wrt=1,mutex=0,readcnt=0;
int wait(int S)
{
	return --S;
}
int signal(int S)
{
	return ++S;
}
void writer()
{
	do
	{
    // writer requests for critical section
         printf("\nwriter is trying to enter");
    wrt = wait(wrt);  
   
    // performs the write
	printf("\nwriter is Writing\n");
             

    // leaves the critical section
    wrt = signal(wrt);
	
           printf("\nwriter is leaving");
	} while(0);
}
void reader()
{
	do
	{
    

            printf("\nreader trying to enter");
   
	mutex = wait(mutex);

   // The number of readers has now increased by 1
	readcnt++;                          

   // there is atleast one reader in the critical section this ensure no writer can enter if there is even one reader thus we give preference to readers here
   	if (readcnt==1)     
      	wrt = wait(wrt);                    

   // other readers can enter while this current reader is inside  the critical section
 	mutex = signal(mutex);                   

   // current reader performs reading here
	printf("\nreader is Reading \n");   	
	mutex = wait(mutex);   // a reader wants to leave

   	readcnt--;

   // that is, no reader is left in the critical section,
   	if (readcnt == 0) 
   	   wrt = signal(wrt);         // writers can enter

   	mutex = signal(mutex); // reader leaves
           printf("\nreader is leaving");         

	} while(0);
}
void main()
{
	int ch;
	while(1)
	{
		printf("\n1.Reading 2.Writing 3.Exit");
		scanf("%d",&ch);
		if(ch==1)
		reader();
		if(ch==2)
		writer();
		if(ch==3)
		exit(0);
	}
}

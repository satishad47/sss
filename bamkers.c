#include<stdio.h>
#define false 0
#define true 1
int avl[10];
int max[10][10];
int alloc[10][10];
int need[10][10];
int req[10];
int reqP,p,r;

void needfunc()
{
	int i,j;
	printf("NEED\n");
	for(i=0;i<p;i++)
	{
		printf("P%d\t",i);
		for(j=0;j<r;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
			printf("%d\t",need[i][j]);
		}
		printf("\n");
	}	
}
void safety()
{
	int i,j,flag1=0,flag2=1,k=0;
	int work[r];
	int sequence[p];
	for(i=0;i<p;i++)
		sequence[i]=0;
	int finish[p];
	for(i=0;i<p;i++)
		finish[i]=false;
	for(i=0;i<r;i++)
		work[i]=avl[i];
	do
	{
		flag2=0;
		for(j=0;j<p;j++)
		{
			for(i=0;i<r;i++)
			{
				if(need[j][i]<=work[i])
					flag1++;
				//printf("for j=%d loop1 flag1=%d work[j]=%d need[][]=%d\n",j,flag1,work[j],need[j][i]);
			}
			if(finish[j]==false && flag1==r)
			{
				//printf("j=%d\n",j);
				printf("Process %d is executing\n",j);
				printf("Updated work array\n");
				sequence[k]=j;
				k++;
				for(i=0;i<r;i++)
				{	work[i]=work[i]+alloc[j][i];
					printf("%d\t",work[i]);
				}
				printf("\n");
				finish[j]=true;
				
				//printf("loop2 k=%d\n",k);
			}
			flag1=0;
		}
		for(i=0;i<p;i++)
		{
			if(finish[i]==true)
				flag2++;
			//printf("loop3\n");
		}
	}while(flag2!=p);
	printf("Sequence is \n");
	for(i=0;i<p;i++)
		printf("P%d ",sequence[i]);
	printf("\n");
}
void request()
{
	int i,j,flag1=0,flag2=0;
	for(i=0;i<r;i++)
	{
		if(req[i]<=need[reqP][i])
		 	flag1++;
		if(req[i]<=avl[i])
		 	flag2++;
	}
	for(i=0;i<r;i++)
	{
		if(flag1==r)
		{
			if(flag2==r)
			{
				avl[i]=avl[i]-req[i];
				alloc[reqP][i]=alloc[reqP][i]+req[i];
				need[reqP][i]=need[reqP][i]-req[i];
			}
			else
			{
				printf("Process %d must wait.No sufficient resources\n",reqP);
			}
		}
		else
		{
			printf("ERROR, Cannot exceed max claim\n");	
			return ;
		}
	}
}
int main(void)
{
	int i,j;
	printf("Enter no of process\n");
	scanf("%d",&p);
	printf("Enter no of resource type\n");
	scanf("%d",&r);
	printf("Enter total resources");
	for(i=0;i<r;i++)
		scanf("%d",&avl[i]);
	//max array
	printf("Enter max array\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	
	//allocation array
	printf("Enter allocation array\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
	//calculate avl
	
	for(i=0;i<r;i++)
	{
		for(j=0;j<p;j++)
		{
			avl[i]=avl[i]-alloc[j][i];
		}
	}
	//
	printf("available resources array is  ");
	for(i=0;i<r;i++)
		printf("%d\t",avl[i]);
	printf("\n");
	needfunc();
	safety();
	printf("Enter a request array(size 3)\n");
	for(i=0;i<r;i++)
		scanf("%d",&req[i]);
	printf("Enter the process\n");
	scanf("%d",&reqP);
	request();
	needfunc();
	safety();


}

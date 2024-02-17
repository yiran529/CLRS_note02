#include<stdio.h>
#include<stdlib.h>
#define DIVISOR 100
int hash(int data);
void put(int data);
void search(int data); 
int slot[100];
int main()
{
	int i,m;
	for(i=0;i<=99;i++)slot[i]=-1;
	int n,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		put(x);
	}
	printf("Hash table construction is completed!\n"); 
	printf("The number you need to search:\n");
	scanf("%d",&x);
	search(x);
	return 0;
 } 
 
int hash(int data)
 {
 	return data % DIVISOR;
 }
 void put(int data)
 {
 	int count=1;
 	int index=hash(hash(data)+count);
 	 while(slot[index]!=-1)
 	 {
 	 	count++;
 	 	index=hash(hash(data)+count);
	  }
 	 slot[index]=data;
 }
 void search(int data)
 {
 	int count=1;
 	int index=hash(hash(data)+count);
 	 while(slot[index]!=data)
 	 {
 	 	count++;
 	 	index=hash(hash(data)+count);
	  }
 	 printf("%d",index);
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 

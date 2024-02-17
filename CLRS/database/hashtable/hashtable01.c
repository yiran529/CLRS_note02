#include<stdio.h>
#include<stdlib.h>
#define DIVISOR 10
struct hashlist
{
	int data;
	struct hashlist *pre;
	struct hashlist *next;
};//记得打分号 
struct hashlist *p[DIVISOR];
int hash(int data);
void put(int data);
 

int main()
{
	int i;
	for(i=0;i<=9;i++)p[i]=NULL;
	int n,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		put(x);
	}
	struct hashlist *pointer;
	for(i=0;i<=9;i++)
	{
		pointer=p[i];
		printf("p[%d]:",i);
		while(pointer!=NULL)
		{
			printf("%d<-",pointer->data);
			pointer=pointer->pre;
		}
		printf("NULL\n");
	}
	return 0;
 } 
 
int hash(int data)
 {
 	return data % DIVISOR;
 }
 void put(int data)
 {
 	int num=hash(data);
 	struct hashlist *pointer;
	pointer=(struct hashlist*)malloc(sizeof(struct hashlist));
	pointer->data=data;
	pointer->pre=p[num];
	pointer->next=NULL;
	p[num]=pointer; 
 }
 
 
 
 
 
 
 
 
 
 
 
 
 

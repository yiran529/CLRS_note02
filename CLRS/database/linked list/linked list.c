#include<stdio.h>
#include<stdlib.h>
struct linknode
{
	int key;
	struct linknode *pre;
}l;
struct linknode *createlist();//建立后进先出链表，即栈 
void printlist(struct linknode *head); //输出（遍历）链表 
void insertnode(struct linknode *head);//插入节点
void deletenode(struct linknode *head);//删除节点 
 
int main()
{ 	
    struct linknode *head;
	head=createlist();
	printlist(head);
	insertnode(head); 
	return 0;
 } 
 
 struct linknode *createlist()
 {
 	int x;
    struct linknode *p,*head;
	head=NULL;
	scanf("%d",&x);//必须在while前先输入一个x，否则while循环进不去 
	while(x)
	{
		p=(struct linknode*)malloc(sizeof(struct linknode));
		p->key=x;
		p->pre=head;
		head=p;
		scanf("%d",&x);
	}
	return head;
 }
 
 void printlist(struct linknode *head)
 {
 	while(head!=NULL)
	{
		printf("%d ",head->key);
		head=head->pre;
	}
	printf("\n");
 }
 
 void insertnode(struct linknode *head)
 {
 	int x; 
 	scanf("%d",&x);
 	struct linknode *p=(struct linknode*)malloc(sizeof(struct linknode));
 	p->key=x;
 	p->pre=head;
 	head=p;
 	printlist(head);
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

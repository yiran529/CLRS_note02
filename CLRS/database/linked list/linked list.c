#include<stdio.h>
#include<stdlib.h>
struct linknode
{
	int key;
	struct linknode *pre;
}l;
struct linknode *createlist();//��������ȳ�������ջ 
void printlist(struct linknode *head); //��������������� 
void insertnode(struct linknode *head);//����ڵ�
void deletenode(struct linknode *head);//ɾ���ڵ� 
 
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
	scanf("%d",&x);//������whileǰ������һ��x������whileѭ������ȥ 
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

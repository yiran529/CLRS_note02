#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node* p;
	struct node* l;
	struct node* r;
	int data;
};
struct node* root;
void input(); //���� 
void traverse(struct node* head);//������� 
void insert(int data);//����ڵ� 
void dele(int data);//ɾ���ڵ� 
struct node* successor(int data);//���Һ�� 
struct node *search(int data,struct node* head);//���ҽڵ� 
struct node* min(struct node* head);//����dataΪ���ڵ�����Ľڵ��е���Сֵ 
void transplant(struct node *p1,struct node *p2);//��ֲ 

int main()
{
	root=(struct node*)malloc(sizeof(struct node));//�����½�rootָ���뿪��rootָ��Ľṹ��Ĵ洢�ռ� 
	root=NULL;
	input(); 
	printf("Inorder traversal:");
	traverse(root);
	printf("\n");
	printf("The BST construction is completed!\n");
	printf("The number you need to delete:\n");
	int x;
	scanf("%d",&x);
	dele(x);
	printf("Inorder traversal:");
	traverse(root);
	printf("\n");
	return 0;
 } 
 
 void input()
 {
 	int n,x,i;
 	scanf("%d",&n);
 	for(i=1;i<=n;i++)//�������BST 
 	{
 		scanf("%d",&x);
 		insert(x); 
	}
 }
 
 
 void insert(int data)
 {
 	struct node* head=root; 
 	struct node* p0=(struct node*)malloc(sizeof(struct node));//����Ҫ�¿��ٿռ� 
 	p0->data=data;
 	p0->l=p0->r=NULL;
 	if(root==NULL)
 	{
 		root=p0;
 		return;
	 }
 	while(   (data<head->data && head->l!=NULL) || (data>head->data && head->r!=NULL)   )
 	{
 		if(data<head->data)head=head->l;
 		else head=head->r;
	 }
	 if((data<head->data && head->l==NULL)){
	 	head->l=p0;
	 	p0->p=head;
	 }
	 else{
	 	head->r=p0;
	 	p0->p=head;		
	 } 
 }
 
 
 void traverse(struct node* head)
 {
 	if(head!=NULL){
 		traverse(head->l);
 		printf("%d ",head->data);
 		traverse(head->r);
 		
	 }
 	else return;
 }
 struct node* search(int data,struct node* head)//����һ��ָ�����͵��β��Ǳ�Ҫ�� 
 {
 	if(data<head->data)search(data,head->l);
 	else if(data>head->data)search(data,head->r);
 	else return head;
 }
struct node* min(struct node* head)//��headΪ���ڵ����������Сֵ 
{
	if(head->l!=NULL)min(head->l);
	else return head;
}
void transplant(struct node* p1,struct node* p2)//ֻ�������ӵ����ĸ��ڵ㣬���������������ڵ� 
{
	if(p1==root) root=p2;//*******************************ע�⿼���������***************************************
	else if(p1==p1->p->l)p1->p->l=p2;
	else p1->p->r=p2;
	if(p2!=NULL)p2->p=p1->p;//************************ע�������ж�**************************** 
}
 void dele(int data)
 {
 	struct node* x=search(data,root);
 	if(x->l==NULL)transplant(x,x->r);//��Ҫֱ�Ӱ�x��ֵΪNULL�����޷��ı�xԭ��ָ��Ľṹ�壬ֻ�ǵ�����xָ���˿� 
    else if(x->r==NULL)transplant(x,x->l);
 	else{
 		struct node* y=min(x->r);
		 if(y==x->r){
		 	y->l=x->l;
		 	x->l->p=y;
		 	transplant(x,y);
		 } 
		 else{
		 	transplant(y,y->r);
		 	y->l=x->l;
		 	x->l->p=y;
		 	y->r=x->r;
		 	x->r->p=y;
		 	transplant(x,y);
		 }
	 }
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

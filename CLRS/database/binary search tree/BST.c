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
void input(); //输入 
void traverse(struct node* head);//中序遍历 
void insert(int data);//插入节点 
void dele(int data);//删除节点 
struct node* successor(int data);//查找后继 
struct node *search(int data,struct node* head);//查找节点 
struct node* min(struct node* head);//找以data为根节点的树的节点中的最小值 
void transplant(struct node *p1,struct node *p2);//移植 

int main()
{
	root=(struct node*)malloc(sizeof(struct node));//区别新建root指针与开辟root指向的结构体的存储空间 
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
 	for(i=1;i<=n;i++)//随机构建BST 
 	{
 		scanf("%d",&x);
 		insert(x); 
	}
 }
 
 
 void insert(int data)
 {
 	struct node* head=root; 
 	struct node* p0=(struct node*)malloc(sizeof(struct node));//必须要新开辟空间 
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
 struct node* search(int data,struct node* head)//含有一个指针类型的形参是必要的 
 {
 	if(data<head->data)search(data,head->l);
 	else if(data>head->data)search(data,head->r);
 	else return head;
 }
struct node* min(struct node* head)//以head为根节点的子树的最小值 
{
	if(head->l!=NULL)min(head->l);
	else return head;
}
void transplant(struct node* p1,struct node* p2)//只处理被连接的树的根节点，而不管它的其它节点 
{
	if(p1==root) root=p2;//*******************************注意考虑这种情况***************************************
	else if(p1==p1->p->l)p1->p->l=p2;
	else p1->p->r=p2;
	if(p2!=NULL)p2->p=p1->p;//************************注意条件判断**************************** 
}
 void dele(int data)
 {
 	struct node* x=search(data,root);
 	if(x->l==NULL)transplant(x,x->r);//不要直接把x赋值为NULL，这无法改变x原先指向的结构体，只是单纯让x指向了空 
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	node* parent;
	node* left;
	node* right;
	int key;
	int balance_factor;
};
node* root;//为了方便，设置指向根节点的指针为全局变量 
void AVL_build();
void AVL_insert(int x);
void AVL_insert_fixup(node* p);
void AVL_dele(int x);
void AVL_dele_fixup(node* p);
void AVL_traverse();
void search(int x);
void left_rotate(node* p);
void right_rotate(node* p);
int main()
{
	build();
	traverse();
	printf("Delete a node?(Y/N)\n");
	char response;
	if((response=getchar())=='Y')
	{
		int x;
		printf("The key of the node you need to delete:\n");
		scanf("%d",&x);
		dele(x);
		traverse();
	 } 
	return 0;
 }
 void AVL_build();
 {
 	int n,i,x;
 	printf("How many nodes you want?\n");
 	scanf("%d",&n);
 	printf("Write them down!");
 	scanf("%d",&x);
 	root=(node*)malloc(sizeof(node));
 	root->key=x;
	root->balance_factor=0;
	root->left=root->right=root->parent=NULL; 
 	for(i=2;i<=n;i++)
 	{
 		scanf("%d",&x);
 		insert(x);
	 }
 }
 void insert(int x)
 {
 	node* p,p0;
 	p=root;
 	while( !((p->left==NULL)&&(x<p->key) || (p->right==NULL)&&(x>p->right)) )
 	{
 		if(x<p->left)p=p->left;
 		else p=p->right;
	 }
	p0=(node*)malloc(sizeof(node));
	p0->parent=p;
	p0->left=p0->right=NULL;
	p0->balance_factor=0;
	p0->key=x;
	if((p->left==NULL)&&(x<p->key))p->left=p0;
	else p->right=p0;
	AVL_insert_fixup(p0);
 }
 void AVL_insert_fixup(node* p)
 {
 	node* p_child;
	do
	{
		if(p==p->parent->left) p->balance_factor++;
		else p->balance_factor--;
		if(p->parent->balance_factor==0)break;/*若p的父节点的平衡因子变为0，说明以p
		  父节点为根节点的子树深度没变，因此其它节点的平衡因子保持不变，没有再fixup的必要，
		  因此退出循环*/
		else if(p->parent->balance_factor==1 ||p->parent->balance_factor==-1)
		{
			p_child=p;
			p=p->parent;
		 } 
		 else
		 {
		 	if(p==p->parent->left && p_child==p->left)
			 {
			 	left_rotate(p->parent);
			 	p->balance_factor=0;
			 	p->right->balance_factor=0;//即原来的p->parent 
			 }
		 	else if (p==p->parent->left && p_child==p->right)
		 	{
				if(p_child->balance_factor==1)
				{
					p->balance_factor=0;
					p->parent->balance_factor=-1;
				}
				else
				{
					p->balance_factor=1;
					p->parent->balance_factor=0;
				}
				p_child->balance_factor=0;
				left_rotate(p);
		 		right_rotate(p_child->parent);//实际上就是原来的p->parent
			 }
			 else if(p==p->parent->right && p_child==p->right)
			 {
			 	right_rotate(p->parent);
			 	p->balance_factor=0;
			 	p->left->balance_factor=0;//即原来的p->parent 
			 }
		 	else if (p==p->parent->left && p_child==p->right)
		 	{
                if(p_child->balance_factor==-1)
				{
					p->balance_factor=0;
					p->parent->balance_factor=1;
				}
				else
				{
					p->balance_factor=-1;
					p->parent->balance_factor=0;
				}
				p_child->balance_factor=0;
				right_rotate(p);
		 		left_rotate(p_child->parent);//实际上就是原来的p->parent
			 }
		 }
	 } while(p!=root);
 }
 void left_rotate(node* p)
 {
 	node* p0=p->right->left;
 	if(p!=root && p==p->parent->left)
 	{
 		p->parent->left=p->right;
 		p->right->parent=p->parent;
 		p->parent->left->left=p;
 		p->parent=p->parent->left;
	 }
 		
 	else if(p!=root && p==p->parent->right)
 	{
 		p->parent->right=p->right;
 		p->right->parent=p->parent;
 		p->parent->right->left=p;
 		p->parent=p->parent->right;
	 }
 	else 
	 {
	 	root=p->right;
	 	root->left=p;
	 	p->parent=root;
	 }
 	p0->parent=p;
 	p->right=p0;
 }
 
 void right_rotate(node* p)
 {
 	node* p0=p->left->right;
 	if(p!=root && p==p->parent->left)
 	{
 		p->parent->left=p->left;
 		p->left->parent=p->parent;
 		p->parent->left->right=p;
 		p->parent=p->parent->left;
	 }
 		
 	else if(p!=root && p==p->parent->right)
 	{
 		p->parent->right=p->left;
 		p->left->parent=p->parent;
 		p->parent->right->right=p;
 		p->parent=p->parent->right;
	 }
 	else 
	 {
	 	root=p->left;
	 	root->right=p;
 		p->parent=root;
	 }
 	p0->parent=p;
 	p->right=p0;
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  

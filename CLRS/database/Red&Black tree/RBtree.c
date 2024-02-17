#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
struct node
{
	struct node* p;
	struct node* l;
	struct node* r;
	int color;//0-红色 1-黑色 
	int data;
};
struct node* NIL;//******注意要让根节点的父节点和叶节点的子节点都指向NIL 
struct node* root;
void input(); //输入 
void traverse(struct node* head);//中序遍历 
void insert(int data);//插入节点 
void dele(int data);//删除节点 
struct node* successor(int data);//查找后继 
struct node *search(int data,struct node* head);//查找节点 
struct node* min(struct node* head);//找以data为根节点的树的节点中的最小值 
void transplant(struct node *p1,struct node *p2);//移植 
void RB_insert_fixup(struct node* x);//插入操作后调整红黑树，使之恢复性质4，即红色节点的孩子为黑色节点 
void RB_dele_fixup(struct node* x);//删除操作后调整红黑树，使之恢复性质1、2、4
void left_rotate(struct node* x);//左旋 
void right_rotate(struct node* x);//右旋 

int main()
{
	root=(struct node*)malloc(sizeof(struct node));//
	NIL=(struct node*)malloc(sizeof(struct node));
	NIL->color=1;//注意要将NIL节点的颜色设为黑色，因为后续有关根节点的操作可能于此有关 
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
 	int n,m,i;
 	scanf("%d",&n);
 	for(i=1;i<=n;i++)//随机构建BST 
 	{
 		scanf("%d",&m);
 		insert(m); 
	}
 }
 
 
 void insert(int data)
 {
 	struct node* head=root; 
 	struct node* p0=(struct node*)malloc(sizeof(struct node));//必须要新开辟空间 
 	p0->data=data;
 	p0->l=p0->r=NIL;//RBtree的修改 
 	p0->color=0;//新节点都着色为RED 
 	if(root==NULL)
 	{
 		root=p0;
 		root->color=1; 
 		root->p=NIL;/************必须在这个位置对根节点的父节点赋值，否则若 在main函数中赋值，然后又把root清空（不得不清空），然后又在insert
		            中把p0赋值给root，这样后来的root的父节点就不是NIL了，于是就会出错*/ 
 		return;
	 }
 	while(   (data<head->data && head->l!=NIL) || (data>head->data && head->r!=NIL)   )
 	{
 		if(data<head->data)head=head->l;
 		else head=head->r;
	 }
	 if((data<head->data && head->l==NIL)){
	 	head->l=p0;
	 	p0->p=head;
	 }
	 else
	 {
	 	head->r=p0;
	 	p0->p=head;		
	 } 
	 RB_insert_fixup(p0); 
 }
 
  void RB_insert_fixup(struct node* x)
 {
 	if(x!=root && x!=root->l && x!=root->r)
	 {
 	struct node* y;//y为叔节点 
 
 	while(x->p->color==0)//在x始终指向红色节点的前提下，若该节点的父节点是红色节点则已没有继续fixup的必要 
	                     //如果x是根节点，自然也会成立，并且此时红黑树的所有性质已经被修复 
 	{
 		if(x->p==x->p->p->l)y=x->p->p->r;
	      else y=x->p->p->l; //y要放在循环里面判断！！！！！！！！！！！！！！！！ 
 		if(x->p==x->p->p->l)//************注意条件判断************* 
 		{
		 	if(y->color==0)
		 	{
		 		x->p->color=1;
		 		y->color=1;
		 		printf("%d\n",y->data) ;
			 	x->p->p->color=0;
			 	x=x->p->p;//要记得x所指对象的转换 
			} 
			else 
			{
		   	 	if(x==x->p->r)
				{
					x=x->p;//注意x所指对象改变为x的父节点 
					left_rotate(x);
				}	
				x->p->color=1;
				x->p->p->color=0;
				right_rotate(x->p->p);
			}
	    }
	    else
		{
			if(y->color==0)
		 	{
		 		x->p->color=1;
		 		y->color=1;
			 	x->p->p->color=0;
			 	x=x->p->p;
			} 
			else 
			{
		   	 	if(x==x->p->l)
				{
					x=x->p;
					right_rotate(x);
				}	
				x->p->color=1;
				x->p->p->color=0;
				left_rotate(x->p->p);
			}
		 } 
	 }
	 root->color=1;//不要忘记处理根节点 
	 }
 }
 
 
 void dele(int data)
 {
 	struct node* x=search(data,root);//x是要被删除的点 
 	struct node* y;/*y不一定是将要被删除的点，而可以看作是一个颜色对红黑树的贡献将要失效的点
	                (因为它将要移到被删节点原来所在的地方，颜色改变，其它性质不变)。它存在的一个意义就是记录原色 */
 	int y_ori_color;
 	struct node* z;//z是将要替代y的一个节点,也即是可能使得性质改变的一个节点 
 	if(x->l==NIL)
	 {
	 	z=x->r;
	 	y=z;
	 	y_ori_color=y->color;////
	 	transplant(x,z);//不要直接把x赋值为NULL，这无法改变x原先指向的结构体
	 } 
    else if(x->r==NIL)
	{
		z=x->l;
		y=z;
		y_ori_color=y->color;////
		transplant(x,z);
	}
 	else{
 		y=min(x->r);///
 		y_ori_color=y->color;//除了y的原色及z，RBtree与BST在这里的操作大致相同 
 		z=y->r;/// 
		 if(y==x->r){
		 	y->l=x->l;
		 	x->l->p=y;
		 	transplant(x,y);//这里只是把y移植到x所在处，并不是把x赋值给y，y的颜色没有变，因此下面一行还要将y的颜色改变为x的颜色 
		 	y->color=z->color;//这一行是必要的，虽然对于dele函数来说没用，但对于delefixup函数而言有用 
		 } 
		 else{
		 	transplant(y,y->r);
		 	y->l=x->l;
		 	x->l->p=y;
		 	y->r=x->r;
		 	x->r->p=y;
		 	transplant(x,y);
		 	y->color=z->color;//
		 }
	 }
	 if(y_ori_color==1)RB_dele_fixup(z);
 }
 
 void RB_dele_fixup(struct node* x)
 {
 	struct node* w;
 	while(x!=root && x->color==1)
 	{
 		if(x==x->p->l)//**********注意*********** 
 		{
 			w=x->p->r;
 			if(w->color==0)//考虑case1这样操作的目的是什么 
 			{
 				left_rotate(x->p);
 				w->color=1;
 				x->p->color=0;
			 }
			 else 
			 {
			 	if(w->l->color==1 && w->r->color==1)
			 	{
					w->color=0;
					x=x->p; 
				 }
				 else if(w->r->color==1)
				 {
				 	right_rotate(w);
				 	w->color=0;
				 	w->p->color=1;
				 }
				 else //case3后必然可以直接到case4，但为了让思路清晰，这里对case4也做一个判断 
				 {
				 	x->p->color=1;
				 	w->r->color=1;
				 	w->color=x->p->color;//注意易忘 
				 	left_rotate(x->p);
				 	x=root;//直接退出循环，用break行不行？不行，因为最后还有一句x->color=1; 
				 }
			 }
		 }
		 else
		 {
		 	w=x->p->l;
 			if(w->color==0)//考虑case1这样操作的目的是什么 
 			{
 				right_rotate(x->p);
 				w->color=1;
 				x->p->color=0;
			 }
			 else 
			 {
			 	if(w->l->color==1 && w->r->color==1)
			 	{
					w->color=0;
					x=x->p; 
				 }
				 else if(w->l->color==1)
				 {
				 	left_rotate(w);
				 	w->color=0;
				 	w->p->color=1;
				 }
				 else //case3后必然可以直接到case4，但为了让思路清晰，这里对case4也做一个判断 
				 {
				 	x->p->color=1;
				 	w->l->color=1;
				 	w->color=x->p->color;//注意易忘 
				 	right_rotate(x->p);
				 	x=root;//直接退出循环，用break不行 
				 }
			 }
		 }
	 }
	 x->color=1;printf("yddddddddddddddddes");//注意！！！ 
 }
 
 void left_rotate(struct node* x)//总共分为三部分 
 {
 	struct node* y;//用y写会简洁些 
 	y=x->r;
 	x->r=y->l;//先移植y的左子树 
 	if(y->l!=NIL)y->l->p=x; //易漏！！！！ 
 	y->p=x->p;
	if(x->p==NIL)root=y;//再处理x的父节点与y的关系
	else if(x==x->p->l)x->p->l=y;
	else x->p->r=y;
	y->l=x;//最后处理x与y的关系 
	x->p=y;
	 
 }
  void right_rotate(struct node* x)
 {
 	struct node* y;
 	y=x->l;
    x->l=y->r;
    if(y->r!=NIL)y->r->p=x; 
    y->p=x->p;
    if(x->p==NIL)root=y;
    else if(x==x->p->l)x->p->l=y;
    else x->p->r=y;
    y->r=x;
    x->p=y;   
 }
 void traverse(struct node* head)
 {
 	if(head!=NIL){
 		traverse(head->l);
 		char c[10];
 		if(head->color==0) strcpy(c,"RED");
 		else strcpy(c,"BLACK");
 		printf("%d(%s)  ",head->data,c);
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
	if(head->l!=NIL)min(head->l);
	else return head;
}
void transplant(struct node* p1,struct node* p2)//只处理被连接的树的根节点，而不管它的其它节点 
{
	if(p1==root) root=p2;//*******************************注意考虑这种情况***************************************
	else if(p1==p1->p->l)p1->p->l=p2;
	else p1->p->r=p2;
	if(p2!=NULL)p2->p=p1->p;//************************注意条件判断**************************** 
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

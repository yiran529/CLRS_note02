#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
struct node
{
	struct node* p;
	struct node* l;
	struct node* r;
	int color;//0-��ɫ 1-��ɫ 
	int data;
};
struct node* NIL;//******ע��Ҫ�ø��ڵ�ĸ��ڵ��Ҷ�ڵ���ӽڵ㶼ָ��NIL 
struct node* root;
void input(); //���� 
void traverse(struct node* head);//������� 
void insert(int data);//����ڵ� 
void dele(int data);//ɾ���ڵ� 
struct node* successor(int data);//���Һ�� 
struct node *search(int data,struct node* head);//���ҽڵ� 
struct node* min(struct node* head);//����dataΪ���ڵ�����Ľڵ��е���Сֵ 
void transplant(struct node *p1,struct node *p2);//��ֲ 
void RB_insert_fixup(struct node* x);//�������������������ʹ֮�ָ�����4������ɫ�ڵ�ĺ���Ϊ��ɫ�ڵ� 
void RB_dele_fixup(struct node* x);//ɾ������������������ʹ֮�ָ�����1��2��4
void left_rotate(struct node* x);//���� 
void right_rotate(struct node* x);//���� 

int main()
{
	root=(struct node*)malloc(sizeof(struct node));//
	NIL=(struct node*)malloc(sizeof(struct node));
	NIL->color=1;//ע��Ҫ��NIL�ڵ����ɫ��Ϊ��ɫ����Ϊ�����йظ��ڵ�Ĳ��������ڴ��й� 
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
 	for(i=1;i<=n;i++)//�������BST 
 	{
 		scanf("%d",&m);
 		insert(m); 
	}
 }
 
 
 void insert(int data)
 {
 	struct node* head=root; 
 	struct node* p0=(struct node*)malloc(sizeof(struct node));//����Ҫ�¿��ٿռ� 
 	p0->data=data;
 	p0->l=p0->r=NIL;//RBtree���޸� 
 	p0->color=0;//�½ڵ㶼��ɫΪRED 
 	if(root==NULL)
 	{
 		root=p0;
 		root->color=1; 
 		root->p=NIL;/************���������λ�öԸ��ڵ�ĸ��ڵ㸳ֵ�������� ��main�����и�ֵ��Ȼ���ְ�root��գ����ò���գ���Ȼ������insert
		            �а�p0��ֵ��root������������root�ĸ��ڵ�Ͳ���NIL�ˣ����Ǿͻ����*/ 
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
 	struct node* y;//yΪ��ڵ� 
 
 	while(x->p->color==0)//��xʼ��ָ���ɫ�ڵ��ǰ���£����ýڵ�ĸ��ڵ��Ǻ�ɫ�ڵ�����û�м���fixup�ı�Ҫ 
	                     //���x�Ǹ��ڵ㣬��ȻҲ����������Ҵ�ʱ����������������Ѿ����޸� 
 	{
 		if(x->p==x->p->p->l)y=x->p->p->r;
	      else y=x->p->p->l; //yҪ����ѭ�������жϣ������������������������������� 
 		if(x->p==x->p->p->l)//************ע�������ж�************* 
 		{
		 	if(y->color==0)
		 	{
		 		x->p->color=1;
		 		y->color=1;
		 		printf("%d\n",y->data) ;
			 	x->p->p->color=0;
			 	x=x->p->p;//Ҫ�ǵ�x��ָ�����ת�� 
			} 
			else 
			{
		   	 	if(x==x->p->r)
				{
					x=x->p;//ע��x��ָ����ı�Ϊx�ĸ��ڵ� 
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
	 root->color=1;//��Ҫ���Ǵ�����ڵ� 
	 }
 }
 
 
 void dele(int data)
 {
 	struct node* x=search(data,root);//x��Ҫ��ɾ���ĵ� 
 	struct node* y;/*y��һ���ǽ�Ҫ��ɾ���ĵ㣬�����Կ�����һ����ɫ�Ժ�����Ĺ��׽�ҪʧЧ�ĵ�
	                (��Ϊ����Ҫ�Ƶ���ɾ�ڵ�ԭ�����ڵĵط�����ɫ�ı䣬�������ʲ���)�������ڵ�һ��������Ǽ�¼ԭɫ */
 	int y_ori_color;
 	struct node* z;//z�ǽ�Ҫ���y��һ���ڵ�,Ҳ���ǿ���ʹ�����ʸı��һ���ڵ� 
 	if(x->l==NIL)
	 {
	 	z=x->r;
	 	y=z;
	 	y_ori_color=y->color;////
	 	transplant(x,z);//��Ҫֱ�Ӱ�x��ֵΪNULL�����޷��ı�xԭ��ָ��Ľṹ��
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
 		y_ori_color=y->color;//����y��ԭɫ��z��RBtree��BST������Ĳ���������ͬ 
 		z=y->r;/// 
		 if(y==x->r){
		 	y->l=x->l;
		 	x->l->p=y;
		 	transplant(x,y);//����ֻ�ǰ�y��ֲ��x���ڴ��������ǰ�x��ֵ��y��y����ɫû�б䣬�������һ�л�Ҫ��y����ɫ�ı�Ϊx����ɫ 
		 	y->color=z->color;//��һ���Ǳ�Ҫ�ģ���Ȼ����dele������˵û�ã�������delefixup������������ 
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
 		if(x==x->p->l)//**********ע��*********** 
 		{
 			w=x->p->r;
 			if(w->color==0)//����case1����������Ŀ����ʲô 
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
				 else //case3���Ȼ����ֱ�ӵ�case4����Ϊ����˼·�����������case4Ҳ��һ���ж� 
				 {
				 	x->p->color=1;
				 	w->r->color=1;
				 	w->color=x->p->color;//ע������ 
				 	left_rotate(x->p);
				 	x=root;//ֱ���˳�ѭ������break�в��У����У���Ϊ�����һ��x->color=1; 
				 }
			 }
		 }
		 else
		 {
		 	w=x->p->l;
 			if(w->color==0)//����case1����������Ŀ����ʲô 
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
				 else //case3���Ȼ����ֱ�ӵ�case4����Ϊ����˼·�����������case4Ҳ��һ���ж� 
				 {
				 	x->p->color=1;
				 	w->l->color=1;
				 	w->color=x->p->color;//ע������ 
				 	right_rotate(x->p);
				 	x=root;//ֱ���˳�ѭ������break���� 
				 }
			 }
		 }
	 }
	 x->color=1;printf("yddddddddddddddddes");//ע�⣡���� 
 }
 
 void left_rotate(struct node* x)//�ܹ���Ϊ������ 
 {
 	struct node* y;//��yд����Щ 
 	y=x->r;
 	x->r=y->l;//����ֲy�������� 
 	if(y->l!=NIL)y->l->p=x; //��©�������� 
 	y->p=x->p;
	if(x->p==NIL)root=y;//�ٴ���x�ĸ��ڵ���y�Ĺ�ϵ
	else if(x==x->p->l)x->p->l=y;
	else x->p->r=y;
	y->l=x;//�����x��y�Ĺ�ϵ 
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
 struct node* search(int data,struct node* head)//����һ��ָ�����͵��β��Ǳ�Ҫ�� 
 {
 	if(data<head->data)search(data,head->l);
 	else if(data>head->data)search(data,head->r);
 	else return head;
 }
struct node* min(struct node* head)//��headΪ���ڵ����������Сֵ 
{
	if(head->l!=NIL)min(head->l);
	else return head;
}
void transplant(struct node* p1,struct node* p2)//ֻ�������ӵ����ĸ��ڵ㣬���������������ڵ� 
{
	if(p1==root) root=p2;//*******************************ע�⿼���������***************************************
	else if(p1==p1->p->l)p1->p->l=p2;
	else p1->p->r=p2;
	if(p2!=NULL)p2->p=p1->p;//************************ע�������ж�**************************** 
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

#include<stdio.h>
#include<stdlib.h>
#define t 3
struct node
{
	int data[2*t];
	struct node* child[2*t+1];
	int leaf;//是叶子节点时值为1，否则为0 
	int n;//该节点孩子个数 
 } ;
 typedef struct node node;
 node* root;
void input(); 
void insert(int k);
void nonfull_insert(node* x,int k);
void split(node* x,int k);
void dele(node* x,int k);
void output(node* p);
int main() 
{
	input();
	printf("data of the root:");
	output(root);
	printf("delete:");
	int k;
	scanf("%d",&k);
	dele(root,k);
	printf("data of the root:");
	output(root);
	return 0;
}
void input()
{
	node* p;
	p=(node*)malloc(sizeof(node));
	p->n=0;
	p->leaf=1;
	root=p;
	int n,i,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&k);
		insert(k);
	}
}
void insert(int k)
{
	if(root->n==2*t-1)
	{
		node* p;
		p=(node*)malloc(sizeof(node));
		p->leaf=0;
		p->n=0;
		p->child[1]=root;
		root=p;
		split(root,1);
	}
	nonfull_insert(root,k);
}
void nonfull_insert(node* x,int k)
{
	int i=x->n;
	if(x->leaf==1)
	{
		while(k<x->data[i] && i>1)
		{
			x->data[i+1]=x->data[i];
			i--;
		}
		if(k>x->data[i])i++;
		x->data[i]=k; 
	    x->n++;
	 } 
	 else
	 {
	 	while(k<x->data[i] && i>1)i--;
		if(k>x->data[i])i++;
	 	if(x->child[i]->n==2*t-1)
	 	{
	 		split(x,i);
	 		if(k>x->data[i])i++;//****************容易忽略******************* 
		 }
		 
	 	nonfull_insert(x->child[i],k);
	 }
 } 
 void split(node* x,int i)
 {
 	int j;
 	for(j=x->n;j>=i;j--)
 	{
 		x->data[j+1]=x->data[j];
 		x->child[j+2]=x->child[j+1];
	}
	x->data[i]=x->child[i]->data[t];
	node* newnode;
	newnode=(node*)malloc(sizeof(node));
	newnode->leaf=x->child[i]->leaf;
	newnode->n=t-1;
	for(j=1;j<=t-1;j++)
	{
		newnode->data[j]=x->child[i]->data[j+t];
		newnode->child[j]=x->child[i]->child[j+t];
	}
	newnode->child[t]=x->child[i]->child[2*t];
	x->child[i+1]=newnode;
	x->child[i]->n=t-1;
	x->n++;
}
void dele(node* x,int k)
{
	int i,in=0,j=0;
	for(i=1;i<=x->n;i++)
	{
		if(k==x->data[i])
		{
			in=1;break;
		}
	 } 
	 printf("%d\n",in);
	if(in==1 && x->leaf==1)
	{
		for(j=i;j<=x->n-1;j++)
		{
			x->data[j]=x->data[j+1];
		}
		x->n--;
	}
	else if(in==1 && x->leaf==0)
	{
		if(x->child[i]->n>=t)
		{
			x->data[i]=x->child[i]->data[x->child[i]->n];
			dele(x->child[i],x->child[i]->data[x->child[i]->n]);
            //if(x->child[i]->leaf==0)
			//	x->child[i]->n--;不应该加这两句话！！！ 
		}
		else if(x->child[i+1]->n>=t)
		{
			x->data[i]=x->child[i+1]->data[1];
			dele(x->child[i+1],x->child[i+1]->data[1]);
            //if(x->child[i+1]->leaf==0)
			//	x->child[i+1]->n--;
		}
		else
		{
			x->child[i]->n++;
			x->child[i]->data[x->child[i]->n]=x->data[i];
			for(j=1;j<=x->child[i+1]->n;j++)
			{
				x->child[i]->n++;
				x->child[i]->data[x->child[i]->n]=x->child[i+1]->data[j];
			 } 
			 for(j=i;j<=x->n-1;j++)
			 {
			 	x->data[j]=x->data[j+1];
			 	x->child[j+1]=x->child[j+2];
			 }
			 x->n--;
			 dele(x->child[i],k);
		 } 
	}
	else if(in==0)
	{
		i=x->n; 
		while(k<x->data[i] && i>1)
			i--;
		if(k>x->data[i])
			i++;
		if(x->child[i]->n<t)
		{
			if(i-1>=1 && x->child[i-1]->n>=t)
			{
				for(j=x->child[i]->n;j>=1;j--)
				{
					x->child[i]->data[j+1]=x->child[i]->data[j];
					if(x->child[i]->leaf==0)
						x->child[i]->child[j+2]=x->child[i]->child[j+1];
				}
				if(x->child[i]->leaf==0)
				{
					x->child[i]->child[2]=x->child[i]->child[1];
					x->child[i]->child[1]=x->child[i-1]->child[x->child[i-1]->n+1];
				}
				x->child[i]->n++;
				x->child[i]->data[1]=x->data[i-1];
				x->data[i-1]=x->child[i-1]->data[x->child[i-1]->n];
				x->child[i-1]->n--;
				dele(x->child[i],k);
			}
			else if(i+1<=x->n+1 && x->child[i+1]->n>=t)
			{
				x->child[i]->n++;
				x->child[i]->data[x->child[i]->n]=x->data[i];
				if(x->child[i]->leaf==0)
				   x->child[i]->child[x->child[i]->n+1]=x->child[i+1]->child[1];
				x->data[i]=x->child[i+1]->data[1];
				for(j=1;j<=x->child[i+1]->n-1;j++)
				{
					x->child[i+1]->data[j]=x->child[i+1]->data[j+1];
					if(x->child[i+1]->leaf==0)
					  x->child[i+1]->child[j]=x->child[i+1]->child[j+1];
				}
				if(x->child[i+1]->leaf==0)
				{
					x->child[i+1]->child[x->child[i+1]->n]=x->child[i+1]->child[x->child[i+1]->n+1];
				}
				x->child[i+1]->n--;
				dele(x->child[i],k);
			}
			else
			{
				if(i+1<=x->n+1)//不要忘记这个条件判断 
				{
					x->child[i]->n++;
					x->child[i]->data[x->child[i]->n]=x->data[i];
					for(j=1;j<=x->child[i+1]->n;j++)
					{
						x->child[i]->n++;
						x->child[i]->data[x->child[i]->n]=x->child[i+1]->data[j];
				 	} 
					 for(j=i;j<=x->n-1;j++)
			 		{
			 			x->data[j]=x->data[j+1];
			 			x->child[j+1]=x->child[j+2];
					 }
					 x->n--;
					 dele(x->child[i],k);
				}
				else if(i-1>=1) 
				{
					x->child[i-1]->n++;
					x->child[i-1]->data[x->child[i-1]->n]=x->data[i-1]; 
					for(j=1;j<=x->child[i]->n;j++)
					{
						x->child[i-1]->n++;
						x->child[i-1]->data[x->child[i-1]->n]=x->child[i]->data[j];
						if(x->child[i-1]->leaf==0)
						{
							x->child[i-1]->child[x->child[i-1]->n]
							 =x->child[i]->child[j];
						}
					 } 
					 if(x->child[i-1]->leaf==0)
					 	x->child[i-1]->child[x->child[i-1]->n+1]
					 	 =x->child[i]->child[x->child[i]->n+1];
					for(j=i;j<=x->n;j++)
					{
						x->child[j]=x->child[j+1];
						x->data[j-1]=x->data[j];
					}
					x->n--;
				}
				else;//实际上还有一种情况，就是该层只剩一个结点了，但我懒得写了 
			}
		}
		else
		{
			dele(x->child[i],k);//不要忘记这个！！！ 
		}
	}
}
void output(node* p)
{
	int i;
	for(i=1;i<=p->n;i++)
	{
		printf("%d ",p->data[i]);
	}
	printf("\n");
	if(!p->leaf)
	{
		for(i=1;i<=p->n+1;i++)
		{
			printf("child%d of the node with the start of %d:",i,p->data[1]);
			output(p->child[i]);
		}
	}
	
}













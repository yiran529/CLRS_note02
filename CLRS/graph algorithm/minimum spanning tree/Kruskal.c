#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int t=0,edgenum;
struct vertex//记录单个点 
{
	char v;
	struct vertex* pa;//记录父节点 
	int Adjlistnum;//adjacent邻接，用来记录指该顶点在Adjlist中的序号
	struct vertex* head;//这三行用以实现不相交的集合 
	struct vertex* next;
//	struct vertex* tail;//队尾指针好像比较鸡肋，虽然有了它可以直接定位队尾，但在UNION时又需要维护，可能时间复杂度差不多 
};
struct E//边集，即邻接链表 
{
	//int Adjlistnum;//adjacent邻接，用来记录指向其它顶点的顶点在Adjlist中的序号,这样方便从链表的头开始遍历 
	struct E *next; 
	struct E *tail;//用以指向每一条链表的队尾 
	struct vertex *p;
};
struct E *Adjlist[100];//各个顶点在邻接链表中从上往下的顺序，由输入的顺序决定 
struct E2//主要用以处理边的长度的排序 
{
	struct vertex *p1;
	struct vertex *p2;
	int weight;
};
struct E2 *edgeweight[100]; 
int read();
void quicksort(int p,int q);
void Kruskal(); 

int main()
{
	int n=read(); 
	printf("Edge of the MST:\n");
	Kruskal();
}

int read()
{
	int i,j,n,w;
	char c;char e[5];

	printf("输入顶点个数："); 
	scanf("%d",&n);
	printf("\n输入顶点名称(用大小写字母表示，中间不用加空格)：\n");
	struct vertex *p0; 
    getchar();
	for(i=1;i<=n;i++)
	{
		scanf("%c",&c); 
		p0=(struct vertex*)malloc(sizeof(struct vertex));
		p0->v=c;
		p0->Adjlistnum=i; 
		p0->pa=NULL;
		Adjlist[i]=(struct E*)malloc(sizeof(struct E));
		Adjlist[i]->p=p0;//这样理解Adjlist[i]:用同时满足（间接地）存储顶点与作为邻接链表开头两个功能 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
		p0->head=p0;
		p0->next=NULL;
	 } 
	 printf("\n输入边的数量：");
	 scanf("%d",&edgenum); 
	 printf("\n输入边的名称(由两个英文字母表示)以及权重：\n");
	 struct vertex *m;
	 for(i=1;i<=edgenum;i++)
	 {
	 	scanf("%s%d",&e,&w);
		for(j=1;j<=n;j++)
	 	{
	 		if(Adjlist[j]->p->v==e[0])
	 		{
	 			m=Adjlist[j]->p;
	 			break;
			 }
		 }
		for(j=1;j<=n;j++)
	 	{
	 		if(Adjlist[j]->p->v==e[1])
	 		{
	 			Adjlist[m->Adjlistnum]->tail->next=(struct E*)malloc(sizeof(struct E));
	 		    Adjlist[m->Adjlistnum]->tail=Adjlist[m->Adjlistnum]->tail->next;
	 			Adjlist[m->Adjlistnum]->tail->p=Adjlist[j]->p;
	 		    edgeweight[i]=(struct E2*)malloc(sizeof(struct E2));
	 			edgeweight[i]->p1=m;
				edgeweight[i]->p2=Adjlist[j]->p;
				edgeweight[i]->weight=w; 
	 			break;
			 }
		 }
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//必要 
		 e[2]=e[0];
		 e[0]=e[1];
		 e[1]=e[2];//交换e[1]与e[2]的位置，因为是无向图 
		for(j=1;j<=n;j++)
	 	{
	 		if(Adjlist[j]->p->v==e[0])
	 		{
	 			m=Adjlist[j]->p;
	 			break;
			 }
		 }
		for(j=1;j<=n;j++)
	 	{
	 		if(Adjlist[j]->p->v==e[1])
	 		{
	 			Adjlist[m->Adjlistnum]->tail->next=(struct E*)malloc(sizeof(struct E));
	 		    Adjlist[m->Adjlistnum]->tail=Adjlist[m->Adjlistnum]->tail->next;
	 			Adjlist[m->Adjlistnum]->tail->p=Adjlist[j]->p;
	 			break;
			 }
		 }
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//必要
	 }
	 edgeweight[edgenum+1]=NULL;
     getchar();
     return n;
}

void Kruskal()
{
    int i;
    struct vertex* walk,*tail;
    quicksort(1,edgenum);
	for(i=1;i<=edgenum;i++)
	{
	    if(edgeweight[i]->p1->head!=edgeweight[i]->p2->head)//相当于findset(p1)!=findset(p2)
		{
			printf("%c%c\n",edgeweight[i]->p1->v,edgeweight[i]->p2->v);
			//以下进行UNION(p1.set,p2.set) (为了降低实现难度，放弃加权合并的启发式策略)
			tail=edgeweight[i]->p1->head;
			while(tail->next!=NULL)
			{
				tail=tail->next;
			}
			walk=edgeweight[i]->p2->head;
			tail->next=walk;
			while(walk!=NULL)
			{
				 walk->head= edgeweight[i]->p1->head;
				 walk=walk->next;
			}
		}	
	}	
}

void quicksort(int p,int q)//非随机化版本 
{
	if(p<q)
	{
		int head=p-1;//head表示比edgeweight[q]->weight小的数组元素的最后一个 
		int tail=p;//tail表示比edgeweight[q]->weight大的数组元素的最后一个
		struct E2 *t;
		while(tail<q)
		{
			if(edgeweight[tail]->weight<edgeweight[q]->weight)
			{
			   	head++;
				t=edgeweight[tail];
				edgeweight[tail]=edgeweight[head];
				edgeweight[head]=t;
			}
			tail++;
		}
		t=edgeweight[head+1];
		edgeweight[head+1]=edgeweight[q];
		edgeweight[q]=t;
		int i;
	printf("\n"); 
		quicksort(p,head);
		quicksort(head+2,q);
	}
}























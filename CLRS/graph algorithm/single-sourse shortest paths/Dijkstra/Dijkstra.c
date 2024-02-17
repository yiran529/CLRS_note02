#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000
int t=0;
struct vertex//记录单个点 
{
	char v;
	struct vertex* pa;//记录父节点 
	int Adjlistnum;//adjacent邻接，用来记录指该顶点在Adjlist中的序号
	int key;//记录该节点与源节点最短路径距离的上界 
	int Qnum;//记录该节点在堆中的序号，便于维护堆 
};
struct E//边集，即邻接链表 
{
	//int Adjlistnum;//adjacent邻接，用来记录指向其它顶点的顶点在Adjlist中的序号,这样方便从链表的头开始遍历 
	struct E *next; 
	struct E *tail;//用以指向每一条链表的队尾 
	struct vertex *p;
	int weight;//记录边的权重 
};
struct E *Adjlist[100];//各个顶点在邻接链表中从上往下的顺序，由输入的顺序决定 
int read();
void Dijkstra(int n); 
void heap_fixup1(struct vertex* Q[],int x);//堆中元素修改后进行堆的维护 
void heap_fixup2(struct vertex* Q[],int k);//抽出堆中元素后对堆进行维护 
struct vertex* extract_min(struct vertex* Q[],int k);//抽出堆中最小元素 
void print(int n);
void relax(struct vertex* p1,struct vertex* p2,int weight);

int main()
{
	int n;
	n=read();
	Dijkstra(n);
    print(n);
	return 0;
}

int read()
{
	int i,j,n,edgenum=0,w;
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
		p0->key=MAX;
		Adjlist[i]=(struct E*)malloc(sizeof(struct E));
		Adjlist[i]->p=p0;//这样理解Adjlist[i]:用同时满足（间接地）存储顶点与作为邻接链表开头两个功能 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 Adjlist[1]->p->key=0;//为了方便，直接以第一个输入的节点为源节点 
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
	 			Adjlist[m->Adjlistnum]->tail->weight=w;
	 			break;
			 }
		 }
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//必要 
    }
     getchar();
     return n;
}

void Dijkstra(int n)
{
	int i,k=n;
	struct vertex* Q[200];
	struct vertex* u;//最下优先数列，即堆 
	struct E* walk;
	for(i=1;i<=n;i++)
	{
		Q[i]=Adjlist[i]->p;
		Adjlist[i]->p->Qnum=i; 
	}
	while(Q[1]!=NULL)
	{
		u=extract_min(Q,k);//为了方便，直接以输入的第一个结点为根节点;k的作用是找到堆的最后一个结点 
		k--;
		walk=Adjlist[u->Adjlistnum]->next;
		while(walk!=NULL)
		{
	        relax(Adjlist[u->Adjlistnum]->p,walk->p,walk->weight); 
			heap_fixup1(Q,walk->p->Qnum);
			walk=walk->next;
		}
	 } 
 } 
 
void print(int n)
{
	int i=1;
	printf("%c.pa=none\n",Adjlist[i]->p->v);
	for(i=2;i<=n;i++)
	{
		printf("%c.pa=%c\n",Adjlist[i]->p->v,Adjlist[i]->p->pa->v);
	 } 
 } 
 
 struct vertex* extract_min(struct vertex* Q[],int k)
 {
 	struct vertex* u=Q[1];
 	if(k!=1)
 	{
		Q[1]=Q[k];
 		heap_fixup2(Q,k);
 
	 }
    else//便于判断Q为空 
    {
    	Q[1]=NULL;
	}
	return u;
 }
 
 void heap_fixup1(struct vertex* Q[],int x)
 {
 	struct vertex* t;
 	while(x!=1 && Q[x]->key<Q[x/2]->key)
 	{
 		Q[x]->Qnum=x/2;
 		Q[x/2]->Qnum=x;//差点忘了…… 
 		t=Q[x];
 		Q[x]=Q[x/2];
 		Q[x/2]=t;
 		x=x/2;
	 }
 }
 
 void heap_fixup2(struct vertex* Q[],int k)
 {
 	struct vertex* t;
 	int x=1;
 	while((2*x<=k)&&(Q[x]->key>Q[2*x]->key) || (2*x+1<=k)&&(Q[x]->key>Q[2*x+1]->key) )
 	{
 		if(2*x+1<=k && Q[2*x]->key>Q[2*x+1]->key)
		 {
		 	Q[x]->Qnum=2*x+1;
 	    	Q[2*x+1]->Qnum=x;//差点忘了…… 
 		    t=Q[x];
 			Q[x]=Q[2*x+1];
 			Q[2*x+1]=t;
 			x=x*2+1;
		 }
 	    else 
 	    {
 	    	Q[x]->Qnum=2*x;
 	    	Q[2*x]->Qnum=x;//差点忘了…… 
 		    t=Q[x];
 			Q[x]=Q[2*x];
 			Q[2*x]=t;
 			x=x*2;
		 }
	 }
 }
 
 void relax(struct vertex* p1,struct vertex* p2,int weight) 
{
	if(p1->key+weight<p2->key)
	{
		p2->key=p1->key+weight;
		p2->pa=p1;
	}
 } 
 
 
 
 
 
 
 
 
 
 
 


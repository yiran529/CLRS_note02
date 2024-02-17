#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int t=0;
struct vertex//记录单个点 
{
	int findtime,finishtime,color;//0白色，1灰色，2黑色 
	char v;
	struct vertex* pa;//记录父节点 
	int Adjlistnum;//adjacent邻接，用来记录指该顶点在Adjlist中的序号
};
struct E//边集，即邻接链表 
{
	//int Adjlistnum;//adjacent邻接，用来记录指向其它顶点的顶点在Adjlist中的序号,这样方便从链表的头开始遍历 
	struct E *next; 
	struct E *tail;//用以指向每一条链表的队尾 
	struct vertex *p;
};
struct E *Adjlist[100];//各个顶点在邻接链表中从上往下的顺序，由输入的顺序决定 
void DFS(int x);
int main()
{
	int i,j,n,edgenum;
	char c;char e[5];

	printf("输入顶点个数："); 
	scanf("%d",&n);
	printf("\n输入顶点名称(用大小写字母表示)：\n");
	struct vertex *p0; 
    getchar();
	for(i=1;i<=n;i++)
	{
		scanf(" %c",&c); 
		p0=(struct vertex*)malloc(sizeof(struct vertex));
		p0->color=p0->findtime=p0->finishtime=0;
		p0->v=c;
		p0->Adjlistnum=i; 
		p0->pa=NULL;
		Adjlist[i]=(struct E*)malloc(sizeof(struct E));
		Adjlist[i]->p=p0;//这样理解Adjlist[i]:用同时满足（间接地）存储顶点与作为邻接链表开头两个功能 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 
	 printf("\n输入边的数量：");
	 scanf("%d",&edgenum); 
	 printf("\n输入边(由两个英文字母表示)：\n");
	 struct vertex *m;
	 for(i=1;i<=edgenum;i++)
	 {
	 	scanf("%s",&e);
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
     getchar();
    for(i=1;i<=n;i++)
	{
		if(Adjlist[i]->p->color==0)
		DFS(i); 
	}
	char parent[10];
	for(i=1;i<=n;i++)
	{
		strcpy(parent,"x");
		if(Adjlist[i]->p->pa==NULL)strcpy(parent,"none");
		    else parent[0]=Adjlist[i]->p->pa->v;
		printf("%c findtime:%d finishtime:%d parent:%s\n",
		Adjlist[i]->p->v,Adjlist[i]->p->findtime,Adjlist[i]->p->finishtime,parent);
	}
	return 0;
}

void DFS(int x)//DFS函数大体上分为三部分,即发现父顶点，深度优先搜索子顶点，回溯至父顶点 
{
	t++;
	Adjlist[x]->p->color=1;
	Adjlist[x]->p->findtime=t;
	struct E *walk;
	walk=Adjlist[x]->next;
	while(walk!=NULL)
	{
		if(walk->p->color==0)
		{
		    walk->p->pa=Adjlist[x]->p;//不要把这句话写在第二层循环之外 
			DFS(walk->p->Adjlistnum); 
		}
		walk=walk->next;
	}
	Adjlist[x]->p->color=2;
	t++; 
	Adjlist[x]->p->finishtime=t;
}





















#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000//以1000000代表无穷 
int t=0,edgenum,n;
struct vertex//记录单个点 
{
	char v;
	struct vertex* pa;//记录父节点 
	int Adjlistnum;//adjacent邻接，用来记录指该顶点在Adjlist中的序号
	int key;//该节点到源节点最短路径的上界 
};
struct E//边集，即邻接链表 
{
	//int Adjlistnum;//adjacent邻接，用来记录指向其它顶点的顶点在Adjlist中的序号,这样方便从链表的头开始遍历 
	struct E *next; 
	struct E *tail;//用以指向每一条链表的队尾 
	struct vertex *p;
	int weight;
};
struct E *Adjlist[100];//各个顶点在邻接链表中从上往下的顺序，由输入的顺序决定 
void Bellman_Ford(); 
void relax(struct vertex* p1,struct vertex* p2,int weight);
void read(); 
void print();
int main()
{
	read();
    Bellman_Ford();
    print();
	return 0;
}

void read()
{
	int i,j;
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
		p0->v=c;
		p0->Adjlistnum=i; 
		p0->pa=NULL;
		p0->key=MAX;
		Adjlist[i]=(struct E*)malloc(sizeof(struct E));
		Adjlist[i]->p=p0;//这样理解Adjlist[i]:用同时满足（间接地）存储顶点与作为邻接链表开头两个功能 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 
	 printf("\n输入边的数量：");
	 scanf("%d",&edgenum); 
	 printf("\n输入边(由两个英文字母表示)：\n");
	 struct vertex *m;
	 int w;
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
     Adjlist[1]->p->key=0;//为了方便，以第一个输入的节点为源节点 
}
void Bellman_Ford()
{
	int i,j;
	struct E* walk;
	for(i=1;i<=n-1;i++)
	{
		for(j=1;j<=n;j++)//***************不要忘记了第二层循环************** 
		{
			walk=Adjlist[j]->next;
			while(walk!=NULL)
			{
				relax(Adjlist[j]->p,walk->p,walk->weight);//注意边的方向，也即要注意函数参数的顺序
				walk=walk->next;
			}
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
 
 void print()
 {
 	int i;
 	printf("Source vertex:%c\n",Adjlist[1]->p->v);
 	printf("The edge of the shortest paths:\n");
 	for(i=2;i<=n;i++)
 	{
 		printf("%c-->%c\n",Adjlist[i]->p->pa->v,Adjlist[i]->p->v);
	 }
 }
  
 
 
 
 
 
 
 
 
 
 
 
 


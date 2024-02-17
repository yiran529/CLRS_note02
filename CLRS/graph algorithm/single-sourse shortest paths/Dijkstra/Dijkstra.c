#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000
int t=0;
struct vertex//��¼������ 
{
	char v;
	struct vertex* pa;//��¼���ڵ� 
	int Adjlistnum;//adjacent�ڽӣ�������¼ָ�ö�����Adjlist�е����
	int key;//��¼�ýڵ���Դ�ڵ����·��������Ͻ� 
	int Qnum;//��¼�ýڵ��ڶ��е���ţ�����ά���� 
};
struct E//�߼������ڽ����� 
{
	//int Adjlistnum;//adjacent�ڽӣ�������¼ָ����������Ķ�����Adjlist�е����,��������������ͷ��ʼ���� 
	struct E *next; 
	struct E *tail;//����ָ��ÿһ������Ķ�β 
	struct vertex *p;
	int weight;//��¼�ߵ�Ȩ�� 
};
struct E *Adjlist[100];//�����������ڽ������д������µ�˳���������˳����� 
int read();
void Dijkstra(int n); 
void heap_fixup1(struct vertex* Q[],int x);//����Ԫ���޸ĺ���жѵ�ά�� 
void heap_fixup2(struct vertex* Q[],int k);//�������Ԫ�غ�Զѽ���ά�� 
struct vertex* extract_min(struct vertex* Q[],int k);//���������СԪ�� 
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

	printf("���붥�������"); 
	scanf("%d",&n);
	printf("\n���붥������(�ô�Сд��ĸ��ʾ���м䲻�üӿո�)��\n");
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
		Adjlist[i]->p=p0;//�������Adjlist[i]:��ͬʱ���㣨��ӵأ��洢��������Ϊ�ڽ�����ͷ�������� 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 Adjlist[1]->p->key=0;//Ϊ�˷��㣬ֱ���Ե�һ������Ľڵ�ΪԴ�ڵ� 
	 printf("\n����ߵ�������");
	 scanf("%d",&edgenum); 
	 printf("\n����ߵ�����(������Ӣ����ĸ��ʾ)�Լ�Ȩ�أ�\n");
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
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//��Ҫ 
    }
     getchar();
     return n;
}

void Dijkstra(int n)
{
	int i,k=n;
	struct vertex* Q[200];
	struct vertex* u;//�����������У����� 
	struct E* walk;
	for(i=1;i<=n;i++)
	{
		Q[i]=Adjlist[i]->p;
		Adjlist[i]->p->Qnum=i; 
	}
	while(Q[1]!=NULL)
	{
		u=extract_min(Q,k);//Ϊ�˷��㣬ֱ��������ĵ�һ�����Ϊ���ڵ�;k���������ҵ��ѵ����һ����� 
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
    else//�����ж�QΪ�� 
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
 		Q[x/2]->Qnum=x;//������ˡ��� 
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
 	    	Q[2*x+1]->Qnum=x;//������ˡ��� 
 		    t=Q[x];
 			Q[x]=Q[2*x+1];
 			Q[2*x+1]=t;
 			x=x*2+1;
		 }
 	    else 
 	    {
 	    	Q[x]->Qnum=2*x;
 	    	Q[2*x]->Qnum=x;//������ˡ��� 
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
 
 
 
 
 
 
 
 
 
 
 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int t=0;
struct vertex//��¼������ 
{
	int findtime,finishtime,color;//0��ɫ��1��ɫ��2��ɫ 
	char v;
	struct vertex* pa;//��¼���ڵ� 
	int Adjlistnum;//adjacent�ڽӣ�������¼ָ�ö�����Adjlist�е����
};
struct E//�߼������ڽ����� 
{
	//int Adjlistnum;//adjacent�ڽӣ�������¼ָ����������Ķ�����Adjlist�е����,��������������ͷ��ʼ���� 
	struct E *next; 
	struct E *tail;//����ָ��ÿһ������Ķ�β 
	struct vertex *p;
};
struct E *Adjlist[100];//�����������ڽ������д������µ�˳���������˳����� 
void DFS(int x);
int main()
{
	int i,j,n,edgenum;
	char c;char e[5];

	printf("���붥�������"); 
	scanf("%d",&n);
	printf("\n���붥������(�ô�Сд��ĸ��ʾ)��\n");
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
		Adjlist[i]->p=p0;//�������Adjlist[i]:��ͬʱ���㣨��ӵأ��洢��������Ϊ�ڽ�����ͷ�������� 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 
	 printf("\n����ߵ�������");
	 scanf("%d",&edgenum); 
	 printf("\n�����(������Ӣ����ĸ��ʾ)��\n");
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
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//��Ҫ 
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

void DFS(int x)//DFS���������Ϸ�Ϊ������,�����ָ����㣬������������Ӷ��㣬������������ 
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
		    walk->p->pa=Adjlist[x]->p;//��Ҫ����仰д�ڵڶ���ѭ��֮�� 
			DFS(walk->p->Adjlistnum); 
		}
		walk=walk->next;
	}
	Adjlist[x]->p->color=2;
	t++; 
	Adjlist[x]->p->finishtime=t;
}





















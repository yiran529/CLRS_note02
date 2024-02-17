#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000//��1000000�������� 
int t=0,edgenum,n;
struct vertex//��¼������ 
{
	char v;
	struct vertex* pa;//��¼���ڵ� 
	int Adjlistnum;//adjacent�ڽӣ�������¼ָ�ö�����Adjlist�е����
	int key;//�ýڵ㵽Դ�ڵ����·�����Ͻ� 
};
struct E//�߼������ڽ����� 
{
	//int Adjlistnum;//adjacent�ڽӣ�������¼ָ����������Ķ�����Adjlist�е����,��������������ͷ��ʼ���� 
	struct E *next; 
	struct E *tail;//����ָ��ÿһ������Ķ�β 
	struct vertex *p;
	int weight;
};
struct E *Adjlist[100];//�����������ڽ������д������µ�˳���������˳����� 
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
	printf("���붥�������"); 
	scanf("%d",&n);
	printf("\n���붥������(�ô�Сд��ĸ��ʾ)��\n");
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
		Adjlist[i]->p=p0;//�������Adjlist[i]:��ͬʱ���㣨��ӵأ��洢��������Ϊ�ڽ�����ͷ�������� 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
	 } 
	 
	 printf("\n����ߵ�������");
	 scanf("%d",&edgenum); 
	 printf("\n�����(������Ӣ����ĸ��ʾ)��\n");
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
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//��Ҫ 
	 }
     getchar();
     Adjlist[1]->p->key=0;//Ϊ�˷��㣬�Ե�һ������Ľڵ�ΪԴ�ڵ� 
}
void Bellman_Ford()
{
	int i,j;
	struct E* walk;
	for(i=1;i<=n-1;i++)
	{
		for(j=1;j<=n;j++)//***************��Ҫ�����˵ڶ���ѭ��************** 
		{
			walk=Adjlist[j]->next;
			while(walk!=NULL)
			{
				relax(Adjlist[j]->p,walk->p,walk->weight);//ע��ߵķ���Ҳ��Ҫע�⺯��������˳��
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
  
 
 
 
 
 
 
 
 
 
 
 
 


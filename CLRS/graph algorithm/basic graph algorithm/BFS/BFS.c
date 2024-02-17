#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int t=0;
struct vertex//��¼������ 
{
	int time,color;//0��ɫ��1��ɫ��2��ɫ 
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
struct queue//���������ɫ�ڵ�Ķ��С���ʵ�ϣ��½�һ�����нṹ�����б�Ҫ�� 
{
	struct queue *next;
	struct vertex *p; 
 };
struct E *Adjlist[100];//�����������ڽ������д������µ�˳���������˳����� 
void BFS(int x);
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
		p0->color=p0->time=0;
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
		BFS(i); 
	}
	char parent[10];
	for(i=1;i<=n;i++)
	{
		strcpy(parent,"x");
		if(Adjlist[i]->p->pa==NULL)strcpy(parent,"none");
		    else parent[0]=Adjlist[i]->p->pa->v;
		printf("%c   time:%d   parent:%s\n",Adjlist[i]->p->v,Adjlist[i]->p->time,parent);
	}
	return 0;
}

void BFS(int x)
{

	struct queue *head,*tail;//���г�ʼ�� 
	head=tail=(struct queue*)malloc(sizeof(struct queue));
	head->p=tail->p=Adjlist[x]->p;
	head->next=tail->next=NULL; 
    struct E *walk;
	while(head!=NULL)
	{
		t++;//ÿһ�α�����������ʲô��ɫ�Ľ�㣬ʱ�䶼Ҫ��һ 
		if(Adjlist[x]->p->color==0) //��֤�ǵ�һ�η��ֵĶ��㣬����ʱ������ 
		{
			Adjlist[x]->p->time=t;
		    Adjlist[x]->p->color=1;	
		}
		walk=Adjlist[x]->next;
		while(walk!=NULL)//������������������ģ����ж������в��� 
		{
			t++;
			if(walk->p->color==0)//!!!!!!!!!!!!!!!!!
			{
				walk->p->color=1;
				walk->p->time=t;
				walk->p->pa=Adjlist[x]->p;
				tail->next=(struct queue*)malloc(sizeof(struct queue));//����� 
				tail->next->p=walk->p;//���� 
				tail=tail->next; 
			}
			tail->next=NULL;
			walk=walk->next;//���������ڽ�������Ҫ���������ж����� 
		}
		Adjlist[x]->p->color=2;
		head=head->next;//���� 
		if(head!=NULL)x=head->p->Adjlistnum;
	}
}






















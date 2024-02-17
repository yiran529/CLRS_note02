#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int t=0,edgenum;
struct vertex//��¼������ 
{
	char v;
	struct vertex* pa;//��¼���ڵ� 
	int Adjlistnum;//adjacent�ڽӣ�������¼ָ�ö�����Adjlist�е����
	struct vertex* head;//����������ʵ�ֲ��ཻ�ļ��� 
	struct vertex* next;
//	struct vertex* tail;//��βָ�����Ƚϼ��ߣ���Ȼ����������ֱ�Ӷ�λ��β������UNIONʱ����Ҫά��������ʱ�临�ӶȲ�� 
};
struct E//�߼������ڽ����� 
{
	//int Adjlistnum;//adjacent�ڽӣ�������¼ָ����������Ķ�����Adjlist�е����,��������������ͷ��ʼ���� 
	struct E *next; 
	struct E *tail;//����ָ��ÿһ������Ķ�β 
	struct vertex *p;
};
struct E *Adjlist[100];//�����������ڽ������д������µ�˳���������˳����� 
struct E2//��Ҫ���Դ���ߵĳ��ȵ����� 
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
		Adjlist[i]=(struct E*)malloc(sizeof(struct E));
		Adjlist[i]->p=p0;//�������Adjlist[i]:��ͬʱ���㣨��ӵأ��洢��������Ϊ�ڽ�����ͷ�������� 
		Adjlist[i]->tail=Adjlist[i];
		Adjlist[i]->next=NULL;
		p0->head=p0;
		p0->next=NULL;
	 } 
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
	 		    edgeweight[i]=(struct E2*)malloc(sizeof(struct E2));
	 			edgeweight[i]->p1=m;
				edgeweight[i]->p2=Adjlist[j]->p;
				edgeweight[i]->weight=w; 
	 			break;
			 }
		 }
		 Adjlist[m->Adjlistnum]->tail->next=NULL;//��Ҫ 
		 e[2]=e[0];
		 e[0]=e[1];
		 e[1]=e[2];//����e[1]��e[2]��λ�ã���Ϊ������ͼ 
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
	    if(edgeweight[i]->p1->head!=edgeweight[i]->p2->head)//�൱��findset(p1)!=findset(p2)
		{
			printf("%c%c\n",edgeweight[i]->p1->v,edgeweight[i]->p2->v);
			//���½���UNION(p1.set,p2.set) (Ϊ�˽���ʵ���Ѷȣ�������Ȩ�ϲ�������ʽ����)
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

void quicksort(int p,int q)//��������汾 
{
	if(p<q)
	{
		int head=p-1;//head��ʾ��edgeweight[q]->weightС������Ԫ�ص����һ�� 
		int tail=p;//tail��ʾ��edgeweight[q]->weight�������Ԫ�ص����һ��
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























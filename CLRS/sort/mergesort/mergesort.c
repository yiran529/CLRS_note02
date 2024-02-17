#include<stdio.h>
void mergesort(int begin,int end,int a[]);
void merge(int begin,int end,int a[]);


int main()
{
	int n,i,a[1000];
	scanf("%d\n",&n);
	for(i=1;i<=n;i++)
	{
		if(i<n)scanf("%d ",&a[i]);
		if(i==n)scanf("%d",&a[i]);
	}
	mergesort(1,n,a);
	for(i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
 } 
void merge(int begin,int end,int a[])
{
	int p,q,i,mid,s,b[1000];
	mid=(begin+end)/2;
	p=begin;q=mid+1;s=begin;
	for(i=begin;i<=end;i++)b[i]=a[i];
	while(s<=end)
	{
		if(p<=mid && q<=end)
		{
			if(b[p]<b[q])
			{
				a[s]=b[p];
				p++;
				s++;
			}
			else 
			{
				a[s]=b[q];
				q++;
				s++;
			}
			
		}
		else if(p>mid)
		{
			a[s]=b[q];
			q++;
			s++;
		}
		else if(q>end)
		{
			a[s]=b[p];
			p++;
			s++;
		}
	}
}
void mergesort(int begin,int end,int a[])
{
	int mid=(begin+end)/2;
	if(end>begin)
	{
		mergesort(begin,mid,a);
		mergesort(mid+1,end,a);	
		merge(begin,end,a);
	}
 } 

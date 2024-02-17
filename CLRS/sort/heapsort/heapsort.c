#include<stdio.h>
int a[1000],n,m;
void maxheapify(int i);
int main()
{
	int i;
	scanf("%d\n",&n);
	for(i=1;i<=100;i++)a[i]=-1000000;
	for(i=1;i<=n;i++)
	{
		if(i<n)scanf("%d ",&a[i]);
		else scanf("%d",&a[i]);
	}
	m=n;
 	for(i=n/2;i>=1;i--)
 	{
 		maxheapify(i);
    }
	for(i=n;i>=1;i--)//∂—≈≈–Ú 
 	{
 		printf("%d ",a[1]);
 		a[1]=a[i];
 		m--;
 		maxheapify(1);//Œ¨ª§∂— 
	 }
	return 0;
 } 
 
 
void maxheapify(int i)
 {
 	int left,right,largest,t;
 	left=2*i;right=2*i+1;
 	largest=i;
 	if(left<=m && a[i]<a[left])largest=left;
 	if(right<=m && a[largest]<a[right])largest=right;
 //	printf("%d %d\n",largest,i);
 	if(largest!=i)
	 {
	 	t=a[i];
 	    a[i]=a[largest];
 	    a[largest]=t;
	    maxheapify(largest);
	}
 }


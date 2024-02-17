#include<stdio.h>
int main()
{
	int max,a[100],b[1000],c[1000],i,n;
	max=0;
	scanf("%d\n",&n);
	for(i=0;i<=1000;i++)b[i]=0;
	for (i=1;i<=n;i++)
	{
		if(i<n)scanf("%d ",&a[i]);
		   else scanf("%d",&a[i]);
		b[a[i]]++;
		if(a[i]>max)max=a[i];
	}
	for(i=1;i<=max;i++)
	{
		b[i]=b[i]+b[i-1];
	}
	for(i=n;i>=1;i--)
	{
		c[ b[a[i]] ]=a[i];
		b[a[i]]--;
    }
    for(i=1;i<=n;i++)
      printf("%d ",c[i]);
	return 0;
 } 

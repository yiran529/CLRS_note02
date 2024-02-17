#include<stdio.h>
int main()
{
	int n,i,j,k;
	scanf("%d",&n);
	int a[n];
	for(i=0;i<=n-1;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<=n-1;i++)
	{
		for(j=0;j<=i-1;j++)  //从后往前进行大小判断只需一层循环 
		{
			if(a[i]<a[j])
			{
				int t=a[i];
				for(k=i;k>=j;k--)
				{
					a[k]=a[k-1];
				}
				a[j]=t;
				break;
			 } 
		}
	}
	for(i=0;i<=n-1;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}

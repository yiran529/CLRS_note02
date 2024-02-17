#include<stdio.h>
int a[1000];
void quicksort(int p,int q);
int main()
{
	int n,i;
	scanf("%d\n",&n);
	for(i=1;i<=n;i++)
	{
		if(i<n)scanf("%d ",&a[i]);
		else scanf("%d",&a[i]);
	}
	quicksort(1,n);
	for(i=1;i<=n;i++)
	{
        printf("%d ",a[i]);
	}
	return 0; 
 } 
 void quicksort(int p,int q)
 {
 	int i,j,t;
 	if(p<q)//易忘记，若不写会死循环 
	 {
 	   i=p-1;
 	   for(j=p;j<=q-1;j++)
 	  {
 	     	if(a[j]<a[q])
 		  {
 		    	i++;
 		  	    t=a[j];
 			    a[j]=a[i];
 			    a[i]=t;
		   }
	  }
	    i++;
    	t=a[q];
 	    a[q]=a[i];
    	a[i]=t;
    	quicksort(p,i-1);
	    quicksort(i+1,q);
    }
 }

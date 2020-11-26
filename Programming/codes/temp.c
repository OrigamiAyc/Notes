#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	int n = 0,x = 0,y = 0,i = 0,nums = 0;
	double _nums = 0;
	double *distance = NULL;
	int *locationx = NULL, *locationy = NULL, *number = NULL;

	scanf("%d %d %d",&n,&x,&y);
	distance = (double*)malloc(n*sizeof(double));
	number = (int *)malloc(n*sizeof(int));
	locationx = (int *)malloc(n*sizeof(int));
	locationy = (int *)malloc(n*sizeof(int));

	for ( i = 0; i < n; i++)
	{
		scanf("%d %d",&locationx[i],&locationy[i]);
	}
	for ( i = 0; i < n; i++)
	{
		distance[i] = sqrt((x-locationx[i])*(x-locationx[i])+(y-locationy[i])*(y-locationy[i]));
		number[i] = i;
	}
	for ( i = 0; i < n; i++)
	{
		if (distance[i+1]>=distance[i]);
		else
		{
			_nums = distance[i];
			distance[i] = distance[i+1];
			distance[i+1] = _nums;
			nums = number[i];
			number[i]=number[i+1];
			number[i+1]=nums;
		}
	}
	for ( i = 0; i < 3; i++)
	{
		printf("%d\n",number[i]+1);
	}
	free(locationy);
	free(locationx);
	free(number);
	free(distance);
	return 0;


}

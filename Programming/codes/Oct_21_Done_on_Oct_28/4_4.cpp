#include <stdio.h>

#define MAX(a,b) ((a) > (b)) ? a : b

int main(int argc, char const *argv[])
{
	int a, b, c;
	printf("Please input 3 numbers, seperated with blankspace\n");
	scanf("%d %d %d", &a, &b, &c);
	int tempMax = MAX(a, b);
	int Max = MAX(tempMax, c);
	printf("%d\n", Max);
	return 0;
}

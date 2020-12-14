#include <stdio.h>
#include <math.h>

#define a 2

int main(int argc, char const *argv[])
{
	int n;
	printf("Please input n\n");
	scanf("%d", &n);
	double result = 0;
	for (size_t i = 0; i < n; i++)
	{
		result += (n - i) * a * pow(10, i);
	}
	printf("%lf\n", result);
	// int re = 2 + 22 + 222 + 2222 + 22222;
	// printf("%d\n", re);
	return 0;
}

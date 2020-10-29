#include <stdio.h>

int main(int argc, char const *argv[])
{
	float x, y;
	scanf("%f", &x);
	if (x < 1)
	{
		y = x;
		printf("%f\n", y);
	}
	else if ((x >= 1) && (x < 10))
	{
		y = 2 * x - 1;
		printf("%f\n", y);
	}
	else
	{
		y = 3 * x - 11;
		printf("%f\n", y);
	}

	return 0;
}

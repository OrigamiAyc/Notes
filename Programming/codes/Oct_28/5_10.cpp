#include <stdio.h>

int main(int argc, char const *argv[])
{
	float result = 0;
	float Fibonacci1 = 1, Fibonacci2 = 2;
	for (size_t i = 0; i < 10; i++)
	{
		result += Fibonacci2 / Fibonacci1;
		Fibonacci1 += Fibonacci2;
		result += Fibonacci1 / Fibonacci2;
		Fibonacci2 += Fibonacci1;
	}
	printf("%f\n", result);
	return 0;
}

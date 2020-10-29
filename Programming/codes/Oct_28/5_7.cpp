#include <stdio.h>

int main(int argc, char const *argv[])
{
	float result;
	for (size_t i = 1; i < 101; i++)
	{
		result += (float)i;
	}
	for (size_t i = 1; i < 51; i++)
	{
		result += (float)(i * i);
	}
	for (size_t i = 1; i < 11; i++)
	{
		result += 1.0 / i;
	}
	printf("%f\n", result);
	return 0;
}

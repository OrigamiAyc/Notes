#include <stdio.h>

int main(int argc, char const *argv[])
{
	int digit1, digit2, digit3;
	for (int i = 100; i < 1000; i++)
	{
		digit1 = i % 10;
		digit2 = (i / 10) % 10;
		digit3 = (i / 100) % 10;
		int cubic = (digit1 * digit1 * digit1) + (digit2 * digit2 * digit2) + (digit3 * digit3 * digit3);
		if (cubic == i)
		{
			printf("%d\n", i);
		}
	}

	return 0;
}

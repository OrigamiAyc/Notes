#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int yanghui[10][10]; // 10 lines
	memset(yanghui, 0, 10 * 10 * sizeof(int));
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			printf("%d\t", yanghui[i][j]);
		}
		printf("\n");
	}

	return 0;
}

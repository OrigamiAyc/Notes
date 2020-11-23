// Insert a number to a sorted array

#include <stdio.h>

int main(int argc, char const *argv[])
{
	int oldArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int newArray[11];
	int a;
	scanf("%d", &a);
	int cnt = 0;
	for (size_t i = 0; i < 10; i++)
	{
		newArray[cnt] = oldArray[i];
		if ((oldArray[i] < a) && (oldArray[i + 1] >= a))
		{
			cnt++;
			newArray[cnt] = a;
		}
		cnt++;
	}
	for (size_t i = 0; i < 11; i++)
	{
		printf("%d ", newArray[i]);
	}
	printf("\n");
	return 0;
}


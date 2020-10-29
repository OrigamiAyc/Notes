#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char input[10];
	printf("Please input a no-more-than-5-digits number\n");
	scanf("%s", input);
	int length = strlen(input);
	printf("%d\n", length);
	for (size_t i = 0; i < length; i++)
	{
		printf("%c\n", input[i]);
	}
	for (int i = length - 1; i >= 0; i--)
	{
		printf("%c", input[i]);
	}
	printf("\n");
	return 0;
}

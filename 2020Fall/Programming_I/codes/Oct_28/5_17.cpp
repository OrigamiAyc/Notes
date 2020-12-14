// array sequences stand for A(0), B(1), C(2)
// while its value stands for X(0), Y(1), Z(2)
// do not need an array, just 3 fors
#include <stdio.h>

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if ((i == j) || (j == k) || (i == k))
				{
					continue;
				}
				else if ((i == 0) || (k == 0) || (k == 2))
				{
					continue;
				}
				else
				{
					char forA, forB, forC;
					forA = (char)i + 'X';
					forB = (char)j + 'X';
					forC = (char)k + 'X';
					printf("A -> %c\tB -> %c\tC -> %c\n", forA, forB, forC);
				}
			}
		}
	}
	return 0;
}

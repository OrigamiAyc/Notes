#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
	int a = 3, b = 4, c = 5;
	int x, y;
	bool out1 = (a + b > c) && (b == c);   // false
	bool out2 = (a || (b - c)) && (b - c); // true
	bool out3 = !(a > b) && ((!c) || 1); // true
	bool out4 = (!(x = a)) && (y = b) && 0; // false
	bool out5 = (!(a + b) + c - 1) && (b + (c / 2)); // true
	printf("%d%d%d%d%d\n", out1, out2, out3, out4, out5);
	return 0;
}

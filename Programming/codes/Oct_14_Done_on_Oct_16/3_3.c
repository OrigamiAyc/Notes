#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	int d = 300000;
	int p = 6000;
	float r = 0.01;
	float m = (log(p / (p - (d * r)))) / (log(1 + r));
	printf("%.1f\n", m);
	return 0;
}

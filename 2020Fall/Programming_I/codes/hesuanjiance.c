#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	int locaX;
	int locaY;
	int sequ;
	double distance;
} CheckPoint;

int distanceCmp(const void *_a, const void *_b);

int main(int argc, const char** argv) {
	int n = 0, X = 0, Y = 0;
	scanf("%d %d %d", &n, &X, &Y);
	CheckPoint *stations = (CheckPoint *)malloc(n * sizeof(CheckPoint));
	for (size_t i = 0; i < n; i++)
	{
		scanf("%d %d", &stations[i].locaX, &stations[i].locaY);
		stations[i].sequ = i;
		stations[i].distance = sqrt(pow((double)(X - stations[i].locaX), 2) + pow((double)(Y - stations[i].locaY), 2));
	}
	qsort(stations, n, sizeof(CheckPoint), distanceCmp);
	for (size_t i = 0; i < 3; i++)
	{
		printf("%d\n", stations[i].sequ + 1);
	}
	free(stations);
	return 0;
}

int distanceCmp(const void *_a, const void *_b)
{
	CheckPoint *a = (CheckPoint *)_a;
	CheckPoint *b = (CheckPoint *)_b;
	if (a->distance - b->distance > 1e-7)
	{
		return 1;
	}
	else if (b->distance - a->distance > 1e-7)
	{
		return -1;
	}
	else
	{
		return (a->sequ - b->sequ);
	}
}

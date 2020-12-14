#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define MAX(a, b) ((a) > (b)) ? a : b

typedef struct
{
	int begin;
	int end;
} region;

int treecmp(const void *_a, const void *_b)
{
	int *a = (int *)_a;
	int *b = (int *)_b;
	return *a - *b;
}

int main(int argc, char const *argv[])
{
	int m, n;
	cin >> n >> m;
	region cut[m];
	for (size_t i = 0; i < m; i++)
	{
		cin >> cut[i].begin >>\
		 cut[i].end;
	}
	qsort(cut, m, sizeof(region), treecmp);
	int remain = cut[0].begin;
	int down = cut[0].end;
	for (size_t i = 0; i < m; i++)
	{
		if (cut[i].begin <= down)
		{
			down = MAX(down, cut[i].end);
		}
		else
		{
			remain += (cut[i].begin - down) - 1;
			down = cut[i].end;
		}
	}
	remain += (n - down);
	cout << remain << endl;
	return 0;
}

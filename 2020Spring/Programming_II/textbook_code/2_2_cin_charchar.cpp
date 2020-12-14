#include <iostream>
#include <math.h>
#include <cstdio>
using namespace std;

#define MAX(a, b) ((a) > (b)) ? a : b

int main(int argc, char const *argv[])
{
	int n = 0;
	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		char begin[5], end[5];
		cin >> begin >> end;
		int x, y;
		x = abs(begin[0] - end[0]);
		y = abs(begin[1] - end[1]);
		int king = MAX(x, y);
		int queen = ((x == 0) || (y == 0) || (x == y)) ? 1 : 2;
		int car = ((x == 0) || (y == 0)) ? 1 : 2;
		int elephant = ((x == y) ? 1 : 2);
		cout << "King: " << king << endl;
		cout << "Queen: " << queen << endl;
		cout << "Car: " << car << endl;
		cout << "Elephant: ";
		if (!((x + y) % 2))
		{
			cout << elephant << endl;
		}
		else
		{
			cout << "Inf" << endl;
		}
	}
	return 0;
}

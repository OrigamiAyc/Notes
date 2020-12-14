#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	int n, m;
	while (scanf("%d %d", &n, &m), n)
	{
		bool ifout[n];
		memset(ifout, 0, n * sizeof(bool));
		int kick = -1;
		for (size_t i = 0; i < n-1; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				kick = (kick + 1) % n;
				while (ifout[kick] == true)
				{
					kick = (kick + 1) % n;
				}
			}
			ifout[kick] = true;
		}
		for (size_t i = 0; i < n; i++)
		{
			if (ifout[i] == false)
			{
				cout << i + 1 << endl;
				break;
			}
		}
	}
	return 0;
}

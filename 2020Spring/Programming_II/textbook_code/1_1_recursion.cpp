#include <iostream>
using namespace std;

void solve(int n, int *l_amount, int *m_amount)
{
	if (n % 2)
	{
		*l_amount = *m_amount = 0;
		return;
	}
	if (n == 0)
	{
		return;
	}
	int less = 0, more = 0;
	solve(n - 2, &less, &more);
	if (n % 4)
	{
		*l_amount = less + 1;
		*m_amount = more + 1;
	}
	else
	{
		*l_amount = less;
		*m_amount = more + 1;
	}
	return;
}

int main(int argc, char const *argv[])
{
	int n = 0;
	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		int Total = 0;
		cin >> Total;
		int l_amount = 0, m_amount = 0;
		solve(Total, &l_amount, &m_amount);
		cout << l_amount << " " << m_amount << endl;
	}
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm>
#include <iostream> 
#include <string.h> 
#include <stdlib.h>
#include <complex>
#include <sstream> 
#include <numeric>
#include <ctype.h> 
#include <stdio.h> 
#include <bitset>
#include <vector> 
#include <string> 
#include <math.h> 
#include <time.h> 
#include <queue> 
#include <stack> 
#include <list>
#include <map> 
#include <set> 
#define Int long long 
#define INF 0x3F3F3F3F 
#define eps 1e-9
using namespace std;

#define N 100009
#define LINF (1LL << 61LL)

struct Line
{
	Int k, b;

	double intersect(const Line &L) const
	{
		return (L.b - b + 0.0) / (k - L.k);
	}
};

// y = k1x + b1
// y = k2x + b2
// x*(k2-k1) + (b2-b1) = 0
// x = (b2-b1)/(k1-k2)

Int T[N], F[N], S[N];

int main()
{
	int n, m, i, j;
	scanf("%d %d", &m, &n);
	for (j = 0; j < m; j++)
		scanf("%lld", &T[j]);
	for (i = 0; i < n; i++)
		scanf("%lld", &F[i]);
	S[0] = 0;
	for (j = 0; j < m; j++)
		S[j + 1] = S[j] + T[j];
	
	vector<Line> st;
	vector<double> X;
	for (j = m - 1; j >= 0; j--)
	{
		Line L = { S[j + 1], -S[j] };
		if (st.empty())
		{
			st.push_back(L);
			continue;
		}
		while (st.size() > 1)
		{
			auto x = L.intersect(st.back());
			if (x > X.back())
			{
				st.pop_back();
				X.pop_back();
			}
			else
			{
				break;
			}
		}
		X.push_back(L.intersect(st.back()));
		st.push_back(L);
	}
	reverse(X.begin(), X.end());
	reverse(st.begin(), st.end());
	X.insert(X.begin(), -1e18);
	Int total = 0;
#ifdef _DEBUG
	Int brute = 0;
#endif
	for (i = 1; i < n; i++)
	{
#ifdef _DEBUG
		Int _t0 = 0;
		for (j = 0; j < m; j++)
		{
			_t0 = max(_t0, F[i - 1] * S[j + 1] - F[i] * S[j]);
		}
		brute += _t0;
#endif

		double x = 1.0 * F[i - 1] / F[i];
		int pos = lower_bound(X.begin(), X.end(), x) - X.begin() - 1;
		Int t0 = st[pos].k * F[i - 1] + st[pos].b * F[i];
		total += t0;
	}
	for (j = 0; j < m; j++)
	{
		total += F[n - 1] * T[j];
#ifdef _DEBUG
		brute += F[n - 1] * T[j];
#endif
	}
	cout << total << endl;
#ifdef _DEBUG
	cout << brute << endl;
#endif
}
/*
1 3
1
2 1 1

2 2
1 2
1 2


*/
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
typedef pair<int, int> pii;

struct Line
{
	Int k, b;

	double intersect(const Line &L) const
	{
		return (b - L.b + 0.0) / (L.k - k);
	}
};

vector<Line> st;
vector<double> X;

void addLine(Int k, Int b)
{
	Line L = { k, b };
	if (st.empty())
	{
		st.push_back(L);
		return;
	}

	while (st.size() > 1)
	{
		auto x = L.intersect(st.back());
		if (x < X.back())
		{
			X.pop_back();
			st.pop_back();
		}
		else
		{
			break;
		}
	}
	X.push_back(L.intersect(st.back()));
	st.push_back(L);
}

Int getMax(Int x)
{
	int pos = lower_bound(X.begin(), X.end(), x + 0.0) - X.begin();
	auto &line = st[pos];
	return line.k * x + line.b;
}

int main()
{
	int n, i;
	scanf("%d", &n);
	vector<pii> t(n), a;
	for (i = 0; i < n; i++)
	{
		scanf("%d %d", &t[i].first, &t[i].second);
	}
	sort(t.begin(), t.end());
	for (i = 0; i < n; i++)
	{
		while (a.size() && a.back().second <= t[i].second)
			a.pop_back();
		a.push_back(t[i]);
	}
	n = a.size();
	vector<Int> dp(n);
	dp[0] = 1ll * a[0].first * a[0].second;
	for (i = 1; i < n; i++)
	{
		addLine(a[i].second, dp[i - 1]);
		auto tmp = getMax(a[i].first);
		dp[i] = min(tmp, 1ll * a[i].first * a[0].second);
	}
	cout << dp.back() << endl;
}
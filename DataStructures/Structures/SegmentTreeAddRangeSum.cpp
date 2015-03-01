#define TESTING 0

/*
 * http://www.codechef.com/CDTR1502/problems/QUERIES/
 */

#pragma comment(linker, "/STACK:500000000")
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
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

struct SegTreeSum {
	vector<Int> sum, a/*dd*/;
	int ppow;

	SegTreeSum(int size) {
		for (ppow = 1; ppow < size; ppow *= 2);
		sum.resize(ppow * 2, 0);
		a.resize(ppow * 2, 0);
	}

	Int getSum(int L, int R) {
		return getSum(1, 0, ppow, L, R);
	}

	void add(int L, int R, Int val) {
		add(1, 0, ppow, L, R, val);
	}

private:
	Int getSum(int v, int l, int r, int L, int R) {
		if (L > R)
			return 0;
		push(v, r - l);
		if (l == L && r - 1 == R)
			return sum[v];
		int mid = (l + r) / 2;
		return getSum(v * 2, l, mid, L, min(R, mid - 1))
			 + getSum(v * 2 + 1, mid, r, max(mid, L), R);
	}

	void add(int v, int l, int r, int L, int R, Int val) {
		if (L > R)
			return;
		if (l == L && r - 1 == R) {
			a[v] += val;
			return;
		}
		push(v, r - l);
		int mid = (l + r) / 2;
		sum[v] += val * (R - L + 1);
		add(v * 2, l, mid, L, min(R, mid - 1), val);
		add(v * 2 + 1, mid, r, max(mid, L), R, val);
	}

	void push(int v, int sz)
	{
		if (v < ppow)
		{
			a[v * 2] += a[v];
			a[v * 2 + 1] += a[v];
		}
		sum[v] += a[v] * sz;
		a[v] = 0;
	}
};

#if TESTING

int main()
{
	int tests, n, q, type, L, R, val;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &n, &q);
		SegTreeSum tree(n);
		while (q--)
		{
			scanf("%d %d %d", &type, &L, &R);
			L--, R--;
			if (type == 0)
			{
				scanf("%d", &val);
				tree.add(L, R, val);
			}
			else
			{
				printf("%lld\n", tree.getSum(L, R));
			}
		}
	}
}

#endif
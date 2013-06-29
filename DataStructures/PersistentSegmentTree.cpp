/*
 * http://www.e-olimp.com/problems/4653
 *
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

const int pw = 20;
const int ppow = 1 << pw;

struct Tree
{
	int t[ppow * 2 * pw];
	int sz;
	int l[ppow * 2 * pw], r[ppow * 2 * pw];
	int top[ppow * 2];
	int curTime;

	void init()
	{
		curTime = 0;
		sz = 2 * ppow;
		for(int i = ppow - 1; i > 0; i--)
			l[i] = i * 2, r[i] = i * 2 + 1;
		top[0] = 1;
	}

	int set(int v, int L, int R, int to, int val)
	{
		int ret = sz++;
		if (L == R)
		{
			t[ret] = val;
			return ret;
		}
		int mid = (L + R) / 2;
		if (to > mid)
		{
			l[ret] = l[v];
			r[ret] = set(r[v], mid + 1, R, to, val);
		}
		else
		{
			r[ret] = r[v];
			l[ret] = set(l[v], L, mid, to, val);
		}
		t[ret] = t[l[ret]] + t[r[ret]];
		return ret;
	}

	void set(int pos, int val)
	{
		int new_node = set(top[curTime], 0, ppow - 1, pos, val);
		top[++curTime] = new_node;
	}

	int getSum(int v, int L, int R, int F, int T)
	{
		if (L == F && R == T)
			return t[v];
		if (F > T)
			return 0;
		int mid = (L + R) / 2;
		return getSum(l[v], L, mid, F, min(T, mid)) + getSum(r[v], mid + 1, R, max(mid + 1, F), T);
	}

	int getSum(int time, int L, int R)
	{
		if (L < 0)
			L = 0;
		return getSum(top[time + 1], 0, ppow - 1, L, R);
	}
};

int A[ppow], B[ppow], pos[ppow];
int x = 0, n;
Tree tree;

int f(int z)
{
	return ((z + x - 1) % n) + 1;
}

int main()
{
	int q, i, j, a, b, c, d;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &A[i]), A[i]--;
	for(i = 0; i < n; i++)
		scanf("%d", &B[i]), B[i]--;
	for(i = 0; i < n; i++)
		pos[B[i]] = i;
	tree.init();
	for(i = 0; i < n; i++)
		tree.set(pos[A[i]], 1);
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d %d %d %d", &a, &b, &c, &d);
		int l1 = min(f(a), f(b)), r1 = max(f(a), f(b)), l2 = min(f(c), f(d)), r2 = max(f(c), f(d));
		l1--, r1--, l2--, r2--;
		x = tree.getSum(r1, l2, r2) - tree.getSum(l1 - 1, l2, r2);
		printf("%d\n", x++);
	}
}

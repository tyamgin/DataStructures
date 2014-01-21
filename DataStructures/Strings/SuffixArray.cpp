/*
	http://www.codechef.com/JULY13/problems/MOU1H/
*/

#if 0

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
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

const int mod = 1000000009;
#define N 200009
#define LOGN 19

int p[N], c[N], pn[N], cn[N], cnt[N], A[N], n, P[LOGN][N], C[LOGN][N];

int lcp(int a, int b, int logn)
{
	int res = 0;
	if ((1 << logn) == n && C[logn][a] == C[logn][b])
		return n;
	for(int h = logn; h >= 0; h--)
	{
		if (a + (1 << h) <= n && C[h][a] == C[h][b])
		{
			res += 1 << h;
			a += 1 << h;
			b += 1 << h;
		}
	}
	return res;
}

int buildSuffArray()
{
	int i, h;
	int alphabet = *max_element(A, A + n) + 1;
	memset(cnt, 0, alphabet * sizeof(int));
	for(i = 0; i < n; i++)
		cnt[A[i]]++;
	for(i = 1; i < alphabet; i++)
		cnt[i] += cnt[i - 1];
	for(i = n - 1; i >= 0; i--)
		p[ --cnt[A[i]] ] = i;
	int classes = 1;
	c[p[0]] = 0;
	for(i = 1; i < n; i++)
	{
		classes += A[p[i]] != A[p[i - 1]];
		c[p[i]] = classes - 1;
	}
	for(h = 0; (1 << h) < n; h++)
	{
		memcpy(C[h], c, n * sizeof(int));
		memcpy(P[h], p, n * sizeof(int));
		for(i = 0; i < n; i++)
		{
			pn[i] = p[i] - (1 << h);
			pn[i] += (pn[i] < 0) * n;
		}
		memset(cnt, 0, classes * sizeof(int));
		for(i = 0; i < n; i++)
			cnt[c[i]]++;
		for(i = 1; i < classes; i++)
			cnt[i] += cnt[i - 1];
		for(i = n - 1; i >= 0; i--)
			p[ --cnt[c[pn[i]]] ] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for(i = 1; i < n; i++)
		{
			int next1 = p[i] + (1 << h);
			next1 -= (next1 >= n) * n;
			int next2 = p[i - 1] + (1 << h);
			next2 -= (next2 >= n) * n;
			classes += c[p[i]] != c[p[i - 1]] || c[next1] != c[next2];
			cn[p[i]] = classes - 1;
		}
		memcpy(c, cn, n * sizeof(int));
	}
	memcpy(C[h], c, n * sizeof(int));
	memcpy(P[h], p, n * sizeof(int));
	return h;
}

int arr[N];

int main()
{
	int i;
	scanf("%*d");
	while(scanf("%d", &n) != EOF)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		for(i = 0; i < n - 1; i++)
			A[i] = arr[i + 1] - arr[i];
		int minV = *min_element(A, A + n - 1);
		for(i = 0; i < n - 1; i++)
			A[i] -= minV - 1;
		A[n - 1] = 0;
		int h = buildSuffArray();
		if ((1 << h) > n)
			h--;
		Int res = (Int)n * (n - 1) / 2;
		for(i = 2; i < n; i++)
			res -= lcp(p[i], p[i - 1], h);
		printf("%d\n", int(res % mod));
	}
}

#endif
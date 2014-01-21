#define TESTING 0

// http://www.codechef.com/problems/SEAGRP/

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

#if TESTING

#define N 109
const int mod = 1e6 + 3;

int d[N][N];
int inverse[mod];
int n;

int det()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (abs(d[j][i]) > abs(d[i][i]))
				swap(d[i], d[j]);
		if (d[i][i] == 0)
			return 0;
		for (int j = i + 1; j < n; j++)
		{
			int c = (Int)d[j][i] * inverse[d[i][i]] % mod;
			for (int k = 0; k < n; k++)
				d[j][k] = (d[j][k] - (Int)c * d[i][k] % mod + mod) % mod;
		}
	}
	return 1;
}

int A[N][N];

bool solve()
{
	if (n % 2)
		return false;
	for (int it = 0; it < 10; it++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
				d[i][j] = A[i][j] ? rand() % mod : 0;
			d[i][i] = 0;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				d[i][j] = (mod - d[j][i]) % mod;
		if (det()) 
			return true;
	}
	return false;
}

int main()
{
	int tests, m, a, b, i;
	inverse[0] = inverse[1] = 1;
	for (i = 2; i < mod; i++)
		inverse[i] = (mod - (long long)mod / i * inverse[mod % i] % mod) % mod;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d %d", &n, &m);
		memset(A, 0, sizeof(A));
		for (i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			a--, b--;
			A[a][b] = A[b][a] = 1;
		}
		puts(solve() ? "YES" : "NO");
	}
}

#endif
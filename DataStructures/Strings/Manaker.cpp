#define TESTING 0

#if TESTING


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

#define N 100009

char s[N];
int d[2][N];

void example(int n)
{
	int l = 0, r = -1, i;
	for(i = 0; i < n; i++)
	{
		int k = i > r ? 1 : min(d[1][l + r - i], r - i);
		while(0 <= i - k && i + k < n && s[i - k] == s[i + k]) 
			k++;
		d[1][i] = k;
		if (i + k - 1 > r)
		{
			r = i + k - 1;
			l = i - k + 1;
		}
	}
	l = 0, r = -1;
	for(i = 0; i < n; i++)
	{
		int k = i > r ? 0 : min(d[0][l + r - i + 1], r - i + 1);
		while(i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) 
			k++;
		d[0][i] = k;
		if (i + k - 1 > r)
		{
			l = i - k;
			r = i + k - 1;
		}
	}
}


#endif
#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <numeric>
#include <sstream> 
#include <fstream>
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

#if 0

#define MAX_MOD 1000009

int vals[MAX_MOD];
vector<int> clear_vals_idxes;
void *_init = memset(vals, -1, sizeof(vals));
map<int, int> generator_cache;

// a^x = b
int discreteLog(int a, int b, int m)
{
	for (int i = 0; i < clear_vals_idxes.size(); i++)
		vals[clear_vals_idxes[i]] = -1;
	clear_vals_idxes.clear();
	int n = (int)sqrt(m + 0.0) + 1;
	int an = 1;
	for (int i = 0; i < n; i++)
		an = (Int)an * a % m;
	for (int i = 1, cur = an; i <= n; i++) 
	{
		if (vals[cur] == -1)
			vals[cur] = i, clear_vals_idxes.push_back(cur);
		cur = (Int)cur * an % m;
	}
	for (int i = 0, cur = b; i <= n; i++) 
	{
		if (vals[cur] != -1) 
		{
			Int ans = (Int)vals[cur] * n - i;
			if (ans < m)
				return ans;
		}
		cur = (Int)cur * a % m;
	}
	return -1;
}

int phi(int n) 
{
	int result = n;
	for (int i = 2; i*i <= n; i++)
	{
		if (n % i == 0) 
		{
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	}
	if (n > 1)
		result -= result / n;
	return result;
}

int modpow(int a, int n, int mod)
{
	int b = 1;
	while (n > 0)
	{
		if (n & 1)
			b = (long long)b * a % mod;
		n >>= 1;
		a = (long long)a * a % mod;
	}
	return b;
}

int generator(int mod) 
{
	if (generator_cache.count(mod))
		return generator_cache[mod];

	vector<int> fact;
	int phi = mod - 1, n = phi;
	for (int i = 2; i*i <= n; i++)
	{
		if (n % i == 0) 
		{
			fact.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n > 1)
		fact.push_back(n);

	for (int res = 2; res <= mod; res++) 
	{
		bool ok = true;
		for (size_t i = 0; i < fact.size() && ok; i++)
			ok &= modpow(res, phi / fact[i], mod) != 1;
		if (ok)
			return generator_cache[mod] = res;
	}
	return generator_cache[mod] = -1;
}

// x^rnk % mod = n
int discreteSqrt(int n, int mod, int rnk = 2)
{
	int g = generator(mod);
	int a = modpow(g, rnk, mod);
	int y = discreteLog(a, n, mod);
	if (y == -1)
		return -1;
	return modpow(g, y, mod);
}

#endif
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

#define MAXN 1000000000

static int primes[] = {2, 5, 7, 11, 13, 17, 19};

class Miller_Rabin
{
	static int modpow(int a, int n, int mod)
	{
		int b = 1;
		while(n > 0)
		{
			if (n & 1)
				b = (long long)b * a % mod;
			n >>= 1;
			a = (long long)a * a % mod;
		}
		return b;
	}

	static bool witness(int a, int n)
	{
		int u = n - 1;
		int t = 1;
		while(~u & 1)
		{
			t++;
			u >>= 1;
		}
		int x0 = modpow(a, u, n);
		for(int i = 0; i < t; i++)
		{
			int x = (long long)x0 * x0 % n;
			if (x == 1)
				return x0 != 1 && x0 != n - 1;
			x0 = x;
		}
		return x0 != 1;
	}

public:
	static bool isPrime(int n, int rounds = 50)
	{
		if (n == 2)
			return true;
		if (n < 2 || (~n & 1))
			return false;
		while(rounds--)
			if (witness(rand() % (n - 1) + 1, n))
				return false;
		return true;
	}

	static bool isPrime2(int n, int rounds = 8)
	{
		if (n == 2)
			return true;
		if (n < 2 || (~n & 1))
			return false;
		for(int round = 0; round < rounds && primes[round] < n; round++)
			if (witness(primes[round], n))
				return false;
		return true;
	}
};

bool isPrime(Int n)
{
	if (n < 2)
		return false;
	for(Int i = 2; i*i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}

bitset<MAXN> prime;

int main()
{
	srand(time(0));
	int i;
	for(i = 2; i < MAXN; i++)
		prime[i] = 1;
	for(i = 2; i*i < MAXN; i++)
		if (prime[i])
			for(int j = i*i; j < MAXN; j += i)
				prime[j] = 0;
	cout << "MAXN = " << MAXN << endl;
	for(int n = 700000000; n < MAXN; n++)
	{
		if (prime[n] != Miller_Rabin::isPrime2(n, 3))
			printf("%d\n", n);
		//printf("%d %d\n", (int)isPrime(n), (int)Miller_Rabin::isPrime(n));
	}
}

#endif

// isPrime
// 1000000 - 4-6

// isPrime2
// first 2 primes for 1000000
// first 3 primes for 10000000
// first 3 primes for 100000000 (except 25326001)
// first 4 primes for 1000000000
// first 3 primes for 1000000000 (except 25326001 161304001 960946321)
// {2, 5, 7}      for 1000000000 (except 746331041)
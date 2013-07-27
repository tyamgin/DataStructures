#define TESTING 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long modmul(long long a, long long b, long long m) 
{
	long long q = (long long)((long double)a * (long double)b / (long double)m);
	long long r = a * b - q * m;
	return (r + 5 * m) % m;
}

long long modpow(long long a, long long n, long long mod)
{
	long long b = 1;
	while(n > 0)
	{
		if (n & 1)
			b = modmul(b, a, mod);
		n >>= 1;
		a = modmul(a, a, mod);
	}
	return b;
}

char witness(long long a, long long n)
{
	long long u = n - 1;
	int t = 1, i;
	while(~u & 1)
	{
		t++;
		u >>= 1;
	}
	long long x0 = modpow(a, u, n);
	for(i = 0; i < t; i++)
	{
		long long x = modmul(x0, x0, n);
		if (x == 1)
			return x0 != 1 && x0 != n - 1;
		x0 = x;
	}
	return x0 != 1;
}

char isPrime(long long n, int rounds)
{
	if (n == 2)
		return 1;
	if (n < 2 || (~n & 1))
		return 0;
	while(rounds--)
		if (witness(rand() % (n - 1) + 1, n))
			return 0;
	return 1;
}

#if TESTING

int main()
{
	srand(time(0));
	int tests;
	scanf("%d", &tests);
	long long n;
	while(tests--)
	{
		scanf("%lld", &n);
		while(!isPrime(n, n < 1e9 ? 1 : 2))
			n--;
		printf("%lld\n", n);
	}
}

#endif
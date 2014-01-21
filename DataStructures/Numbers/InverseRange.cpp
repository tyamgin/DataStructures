#define TESTING 0

// description: http://discuss.codechef.com/questions/3433/modular-multiplicative-inverse

#include <stdio.h>

#if TESTING

const int mod = 1000003;
int inverse[mod];

int main()
{
	inverse[0] = inverse[1] = 1;
	for (int i = 2; i < mod; i++)
		inverse[i] = (mod - (long long)mod / i * inverse[mod % i] % mod) % mod;
}

#endif
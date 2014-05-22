// http://acm.timus.ru/problem.aspx?space=1&num=1854

#if 0

long long gcd(long long a, long long b)
{
	return b ? gcd(b, a % b) : a;
}

long long randLong(long long from, long long to)
{
	return ((long long)(rand() << 16) + (rand() << 32) + rand()) % (to - from + 1) + from;
}

// перед вызовом нужно проверять на простоту
long long PollardRho(long long N)
{
	long long x = randLong(1, N - 2),
		y = 1,
		stage = 2;
	for(long long i = 0; gcd(N, abs(x - y)) == 1; i++)
	{
		if (i == stage)
		{
			y = x;
			stage *= 2;
		}
		x = (mulmod(x, x, N) + 1) % N;
	}
	return gcd(N, abs(x - y));
}

#endif
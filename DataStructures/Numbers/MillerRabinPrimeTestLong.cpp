#define TESTING 0

namespace Factorization
{
	Int gcd(Int a, Int b)
	{
		return b ? gcd(b, a % b) : a;
	}

	Int randLong(Int from, Int to)
	{
		return ((Int)(rand() << 16) + (rand() << 32) + rand()) % (to - from + 1) + from;
	}

	Int _modmul(Int a, Int n, Int mod)
	{
		Int b = 0;
		while (n > 0)
		{
			if (n & 1)
				b = (b + a) % mod;
			n >>= 1;
			a = (a + a) % mod;
		}
		return b;
	}

	// быстрое умножение по модулю
	Int modmul(Int a, Int b, Int m)
	{
		Int q = (Int)((long double)a * (long double)b / (long double)m);
		Int r = a * b - q * m;
		return (r + 5 * m) % m;
	}

	Int modpow(Int a, Int n, Int mod)
	{
		Int b = 1;
		while (n > 0)
		{
			if (n & 1)
				b = modmul(b, a, mod);
			n >>= 1;
			a = modmul(a, a, mod);
		}
		return b;
	}

	// проверка свидетеля простоты
	char witness(Int a, Int n)
	{
		Int u = n - 1;
		int t = 1, i;
		while (~u & 1)
		{
			t++;
			u >>= 1;
		}
		Int x0 = modpow(a, u, n);
		for (i = 0; i < t; i++)
		{
			Int x = modmul(x0, x0, n);
			if (x == 1)
				return x0 != 1 && x0 != n - 1;
			x0 = x;
		}
		return x0 != 1;
	}


	// перед вызовом нужно проверять на простоту
	// возвращает либо 1, либо n, либо любой делитель
	// algo: https://ru.wikipedia.org/wiki/%CE%A1-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9F%D0%BE%D0%BB%D0%BB%D0%B0%D1%80%D0%B4%D0%B0
	Int pollardRho(Int N)
	{
		Int x = randLong(1, N - 2),
			y = 1,
			stage = 2;
		for (Int i = 0; gcd(N, abs(x - y)) == 1; i++)
		{
			if (i == stage)
			{
				y = x;
				stage *= 2;
			}
			x = (modmul(x, x, N) + 1) % N;
		}
		return gcd(N, abs(x - y));
	}

	char isPrime(Int n, int rounds = 50)
	{
		if (n == 2)
			return 1;
		if (n < 2 || (~n & 1))
			return 0;
		while (rounds--)
		{
			if (witness(rand() % (n - 1) + 1, n))
				return 0;
		}
		return 1;
	}

	map<Int, int> factorize(Int n, int primitives = 10000000, int rounds = 50)
	{
		map<Int, int> res;
		for (Int i = 2; i*i <= n && i < primitives; i++)
		{
			while (n % i == 0)
			{
				res[i]++;
				n /= i;
			}
		}

		while (n > 1 && !isPrime(n, rounds))
		{
			Int r = 1;
			while (r == 1 || r == n)
				r = pollardRho(n);

			for (auto p : factorize(r, primitives))
				res[p.first] += p.second;

			n /= r;
		}
		if (n > 1)
			res[n]++;
		return res;
	}
};


#endif
#define N 25009
#define LOGN 15

unsigned Min[LOGN][N], Log[N];

int main()
{
	int n, m, a, b;
	for (int i = 0; (1 << i) < N; i++)
		Log[1 << i] = i;
	for (int i = 2; i < N; i++)
	{
		if (Log[i] == 0)
			Log[i] = Log[i - 1];
	}
	while (1)
	{
		scanf("%d %d %d %d", &n, &m, &a, &b);
		if (n == 0 && m == 0 && a == 0 && b == 0)
			break;
		
		unsigned cur = a + b;
		for (unsigned i = 0; i < n; i++, cur += a)
			Min[0][i] = cur;
		for (int l = 1; l < LOGN; l++)
		{
			for (int i = 0; i < n; i++)
			{
				Min[l][i] = Min[l - 1][i];
				int idx = i + (1 << (l - 1));
				if (idx < n && Min[l][i] > Min[l - 1][idx])
					Min[l][i] = Min[l - 1][idx];
			}
		}
		Int res = 0;
		for (unsigned i = 0; i < m; i++)
		{
			int L = cur % n;
			cur += a;
			int R = cur % n;
			cur += a;
			if (L > R)
				swap(L, R);
			int len = (R - L + 1);
			int log = Log[len];
			res += min(Min[log][L], Min[log][R - len + 1]);
		}
		printf("%lld\n", res);
	}
}
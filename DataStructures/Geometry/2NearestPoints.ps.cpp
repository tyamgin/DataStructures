// http://www.e-olymp.com/ru/problems/4388

#define N 100009
#define LINF 9223372036854775807L

#define SQR(a) ((a)*(a))

// this algo: http://e-maxx.ru/algo/nearest_points

struct Point
{
	Int x, y;

	Int getDistTo2(const Point &p) const
	{
		return SQR(x - p.x) + SQR(y - p.y);
	}

	bool operator <(const Point &p) const
	{
		if (x != p.x)
			return x < p.x;
		return y < p.y;
	}
};

int n;
Point a[N], c[N];
Point resA, resB;
Int res = LINF;

void upd(const Point &a, const Point &b, Int &curRes)
{
	auto dist = a.getDistTo2(b);
	if (dist < curRes)
		curRes = dist;
	if (curRes < res)
        {
                res = curRes;
                resA = a;
		resB = b;
	}
}

Int solve(int L, int R)
{
	if (L + 1 >= R)
		return LINF;

	int mid = (L + R) / 2;
	auto cen = a[mid].x;
	Int h = min(solve(L, mid), solve(mid, R));
	merge(a + L, a + mid, a + mid, a + R, c, [](Point a, Point b) { return a.y < b.y; });
	copy(c, c + (R - L), a + L);
	int sz = 0;
	Int res = h;
	for (int i = L; i < R; i++)
	{
                if (SQR(cen - a[i].x) < h)
                {
		        for (int j = sz - 1; j >= 0 && SQR(a[i].y - c[j].y) < h; j--)
	         		upd(a[i], c[j], res);
                        c[sz++] = a[i];
		}
	}
	return res;
}

int main()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%lld %lld", &a[i].x, &a[i].y);

	sort(a, a + n);
	auto res = solve(0, n);
	printf("%lld %lld\n%lld %lld\n", resA.x, resA.y, resB.x, resB.y);
}

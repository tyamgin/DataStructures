a = convexHull(a);
n = a.size();
double res = 0;
for (int i = 0, j = 2; i < n; i++)
{
	while (abs(vec(a[i], a[(i + 1) % n], a[j])) <= abs(vec(a[i], a[(i + 1) % n], a[(j + 1) % n])))
	{
		j = (j + 1) % n;
	}
	res = max(res, max(a[i].getDistTo(a[j]), a[(i + 1) % n].getDistTo(a[j])));
}
printf("%.13f\n", res);
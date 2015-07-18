/**
 * @source http://e-maxx.ru/algo/assignment_hungary
 * @problem http://www.e-olymp.com/ru/problems/5526
 */
template<typename T> vector<int> assignment(vector<vector<T> > a, T infinity)
{
	int n = a.size(), m = a[0].size();
	for (auto &row : a)
		row.insert(row.begin(), T(0));
	a.insert(a.begin(), vector<T>(a[0].size(), T(0)));

	vector<T> u(n + 1), v(m + 1);
	vector<int> p(m + 1), way(m + 1);
	for (int i = 1; i <= n; i++) 
	{
		p[0] = i;
		int j0 = 0;
		vector<T> minv(m + 1, infinity);
		vector<char> used(m + 1, false);
		do 
		{
			used[j0] = true;
			int i0 = p[j0], j1;
			T delta = infinity;
			for (int j = 1; j <= m; j++)
			{
				if (!used[j]) 
				{
					T cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j])
						minv[j] = cur, way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j], j1 = j;
				}
			}
			for (int j = 0; j <= m; j++)
			{
				if (used[j])
					u[p[j]] += delta, v[j] -= delta;
				else
					minv[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);

		do 
		{
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	vector<int> ans(n);
	for (int j = 1; j <= m; ++j)
		ans[p[j] - 1] = j - 1;
	return ans;
}
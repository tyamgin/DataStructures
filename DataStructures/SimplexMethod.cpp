#define TESTING 1

#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
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

// http://abc.vvsu.ru/Books/ebooks_iskt/%DD%EB%E5%EA%F2%F0%EE%ED%ED%FB%E5%F3%F7%E5%E1%ED%E8%EA%E8/%C8%F1%F1%EB%E5%E4%EE%E2%E0%ED%E8%E5%20%EE%EF%E5%F0%E0%F6%E8%E9/fmi.asf.ru/vavilov/sm6.htm

struct SimplexTable
{
	vector<vector<double> > a;
	vector<double> diff;		// разности
	int rows, columns;
	vector<int> basis;

	double &operator ()(int i, int j) {
		return X(i, j);
	}

	double &operator ()(int i) {
		return X(i);
	}

	double &X(int i, int j) {
		return a[i][j];
	}

	double &X(int i) {
		return a[i][columns];
	}
};

struct SimplexMethod : SimplexTable {
	bool gauss(vector<vector<double> > &a) {
		int j;
		basis.clear();
		for(int row = 0, col = 0; row < rows && col < columns; col++) {
			int pos = row;
			for(j = row; j < rows; j++)
				if (fabs(a[pos][col]) < fabs(a[j][col]))
					pos = j;
			swap(a[row], a[pos]);
			if (fabs(a[row][col]) < eps)
				continue;
			for(j = 0; j < rows; j++) {
				if (row != j) {
					double c = a[j][col] / a[row][col];
					for(int k = 0; k <= columns; k++)
						a[j][k] -= a[row][k] * c;
				}
			}
			basis.push_back(col);
			row++;
		}
		if (basis.size() < rows)
			return false;
		for(int i = 0; i < rows; i++) {
			double center = a[i][basis[i]];
			for(int j = 0; j <= columns; j++)
				a[i][j] /= center;
		}
		return true;
	}

	int getI(int L) {
		double min = 1e100;
		int I = -1;
		for(int i = 0; i < rows; i++)
			if (X(basis[i], L) > eps && min > X(basis[i]) / X(basis[i], L))
				min = X(basis[i]) / X(basis[i], L), I = i;
		return I;
	}

	int Do(vector<vector<double> > _a, vector<double> c, vector<double> &result) {		
		rows = _a.size();
		columns = _a[0].size() - 1;
		if (!gauss(_a))
			return 0;
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j <= columns; j++)
				printf("%.5lf ", _a[i][j]);
			puts("");
		}
		diff.resize(columns);
		a.assign(columns, vector<double>(columns + 1));
		for(int i = 0; i < rows; i++)
			a[basis[i]] = _a[i];
		for(int j = 0; j < columns; j++) {
			double sum = 0;
			for(int i = 0; i < rows; i++)
				sum += c[basis[i]] * a[basis[i]][j];
			diff[j] = sum - c[j];
		}

		while(1) {
			int L = max_element(diff.begin(), diff.end()) - diff.begin();
			if (diff[L] < eps) {
				result.clear();
				for(int i = 0; i < columns; i++)
					result.push_back(X(i));
				return 1;
			}

			int whereI = getI(L);
			if (whereI < 0)
				return INF;
			int I = basis[whereI];
			double teta = X(I) / X(I, L);
			SimplexTable to = *this;
			to(L, columns) = teta; // new x
			for(int j = 0; j < columns; j++)
				to(L, j) = X(I, j) / X(I, L);

			for(int row = 0; row < rows; row++) {
				if (row != whereI) {
					int i = basis[row]; 
					to(i, columns) = X(i) - teta * X(i, L);
					for(int j = 0; j < columns; j++)
						to(i, j) = X(i, j) - X(I, j) / X(I, L) * X(i, L);
				}
			}
			for(int j = 0; j < columns; j++)
				to.diff[j] = diff[j] - X(I, j) / X(I, L) * diff[L];
			basis[whereI] = L;
			a = to.a;
			diff = to.diff;
		}
	}
};

#if TESTING


#define N 109

int A[N][N];

int main()
{
	freopen("D:\\Projects\\ws\\ws\\inp.txt", "r", stdin);

	int n, i, j;
	scanf("%d", &n);
	int rows = n + 1, columns = 2 * n + 1;
	vector<vector<double> > a(rows, vector<double>(columns + 1, 0.0));
	vector<double> c(columns, 0.0);
	c[columns - 1] = -1;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			scanf("%d", &A[i][j]);
			a[i][j] = -A[i][j];
		}
		a[i][i + n] = -1;
		a[i][columns - 1] = 1;
	}
	for(i = 0; i < n; i++)
		a[n][i] = 1;
	a[n][columns] = 1;
	SimplexMethod sm;
	vector<double> res;
	sm.Do(a, c, res);
	for(int i = 0; i < n; i++)
		printf("%.5lf\n", res[i]);
}

/*
int main()
{
	double c[] = {0, 1, -3, 0, 2, 0};
	double a[3][7] = {{1, 3, -1, 0, 2, 0,  7},
			     	  {0, -2, 4, 1, 0, 0,  12},	
				      {0, -4, 3, 0, 8, 1,  10}};
	//double a[3][7] = {{1, 1, 1, 1, 1, 1,  7},
	//		     	  {1, 1, 1, 1, 1, 1,  12},	
	//			      {0, -4, 3, 0, 8, 1,  10}};
	int basis[] = {0, 3, 5};

	vector<vector<double> > A(3);
	for(int i = 0; i < 3; i++)
		A[i].insert(A[i].begin(), a[i], a[i] + 7);
	SimplexMethod sm;
	vector<double> res;
	cout << sm.Do(A, vector<double>(c, c + 7), res) << endl;
	return 0;
}
*/
#endif;
#define TESTING 0

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

template <int size, int mod> 
class QMatrix
{
	int A[size][size];

public:

	int* operator[](int idx)
	{
		return A[idx];
	}

	QMatrix(bool identity = false)
	{
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
				A[i][j] = 0;
			A[i][i] = identity;
		}
	}

	QMatrix operator *(const QMatrix &b) const
	{
		QMatrix res;
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				for(int k = 0; k < size; k++)
					res.A[i][j] = (res.A[i][j] + (long long)A[i][k] * b.A[k][j]) % mod;
		return res;
	}

	QMatrix pow(long long n) const
	{
		QMatrix b(1), a(*this);
		while(n > 0)
		{
			if (n & 1)
				b = b * a;
			n >>= 1;
			a = a * a;
		}
		return b;
	}

	friend istream &operator >>(istream &in, QMatrix &a)
	{
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				in >> a.A[i][j];
		return in;
	}

	friend ostream &operator <<(ostream &out, const QMatrix &a)
	{
		for(int i = 0; i < size; i++)
		{
			out << a.A[i][0];
			for(int j = 1; j < size; j++)
				out << " " << a.A[i][j];
			out << endl;
		}
		return out;
	}

	void read()
	{
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				scanf("%d", &A[i][j]);
	}

	void print()
	{
		for(int i = 0; i < size; i++)
		{
			printf("%d", A[i][0]);
			for(int j = 1; j < size; j++)
				printf(" %d", A[i][j]);
			puts("");
		}
	}
};

#if TESTING
#endif
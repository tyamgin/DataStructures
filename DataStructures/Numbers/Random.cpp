#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <sstream> 
#include <fstream>
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

#if 0

struct Random
{
	static unsigned getUnsigned()
	{
		return (unsigned)rand() * RAND_MAX + rand();
	}

	static double getDouble()
	{
		return (double)getUnsigned() / RAND_MAX / RAND_MAX;
	}

	static double getDouble(double from, double to)
	{
		return getDouble() * (to - from) + from;
	}

	static double getGaussian(double center = 0, double variance = 1)
	{
		double sum = 0;
		for (int i = 0; i < 48; i++)
			sum += getDouble();
		return (sum / 2 - 12) * variance + center;
	}
};

int main()
{
	for (int i = 0; i < 10; i++)
		cout << Random::getGaussian(-10, 1) << endl;
}

#endif
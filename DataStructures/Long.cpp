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

struct Long {
	static long long parse(const char *str) {
		long long result;
		sscanf(str, "%lld", &result);
		return result;
	}

	static long long parse(const string &str) {
		return parse(str.c_str());
	}

	static unsigned long long sqrt(long long a) {
		if (a < 0)
			throw "a <= 0 in Long::sqrt(a)";
		unsigned long long L = 0, R = std::min(a, (1ll << 32ll) - 1), result = 0;
		while(L <= R) 
		{
			unsigned long long c = (L + R) / 2;
			if (c*c <= (unsigned long long)a)
				L = c + 1, result = c;
			else
				R = c - 1;
		}
		return result;
	}

	unsigned short randUnsignedShort() {
		return (unsigned short)rand();
	}

	unsigned randUnsignedInt() {
		return ((unsigned)randUnsignedShort() << 16) + (unsigned)randUnsignedShort();
	}

	unsigned long long randUnsignedLL() {
		return ((unsigned long long)randUnsignedInt() << (unsigned long long)32) + (unsigned long long)randUnsignedInt();
	}
};

#if TESTING

void check()
{
	clock_t timer = clock();
	for(long long i = 1e17; i < 1e17 + 1e7; i++)
		Long::sqrt(i);
	cout << "Long::sqrt(.) " << clock() - timer << endl;

	timer = clock();
	for(long long i = 1e17; i < 1e17 + 1e7; i++)
		sqrt(i + 0.0);
	cout << "sqrt(.) " << clock() - timer << endl;

}

int main()
{
	for(int i = 0; i < 1e6; i++)
		if (Long::sqrt(i) != int(sqrt(i + 0.0) + eps))
			cerr << "Error" << endl;
	cout << Long::sqrt(LLONG_MAX) << endl;
	check();
}

#endif
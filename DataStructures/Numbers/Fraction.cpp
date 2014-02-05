#define TESTING 0
#if TESTING

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

// TODO
// positive only
template <typename Type, Type gcd(Type, Type)> struct Fraction {
	Type num, denum;

	void reduce() {
		Type g = gcd(num > 0 ? num : -num, denum > 0 ? denum : -denum);
		num /= g;
		denum /= g;
	}
	Fraction(Type num = Type(0), Type denum = Type(1)) {
		this->num = num;
		this->denum = denum;
		reduce();
	}
	Fraction operator *(const Fraction &fr) const {
		return Fraction(num * fr.num, denum * fr.denum);
	}
	Fraction operator /(const Fraction &fr) const {
		return Fraction(num * fr.denum, denum * fr.num);
	}
	Fraction operator +(const Fraction &fr) const {
		return Fraction(num * fr.denum + fr.num * denum, denum * fr.denum);
	}
	Fraction operator -(const Fraction &fr) const {
		return Fraction(num * fr.denum - fr.num * denum, denum * fr.denum);
	}
	Fraction operator +(Type b) const {
		return operator +(*new Fraction(b));
	}
	Fraction operator -(Type b) const {
		return operator -(*new Fraction(b));
	}
};

template <typename Type, Type gcd(Type, Type)>
ostream &operator <<(ostream &out, Fraction<Type, gcd> fr) {
	return out << fr.num << '/' << fr.denum;
}

template <typename Type, Type gcd(Type, Type)>
istream &operator >>(istream &in, Fraction<Type, gcd> &fr) {
	fr.denum = Type(1);
	return in >> fr.num;
}

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int main()
{
	Fraction<int, gcd> a(2, 4);
	Fraction<int, gcd> b(1, 2);
	cout << a + b << endl;
}

#endif
#if 0

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

#define det(a,b,c,d) ((a)*(d)-(b)*(c))

const double Pi = acos(-1.0);

struct Point3D
{
	double x, y, z;

	Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z)
	{

	}

	// разность векторов
	Point3D operator -(Point3D p) const
	{
		return Point3D(x - p.x, y - p.y, z - p.z);
	}

	// унарный минус
	Point3D operator -() const
	{
		return Point3D(-x, -y, -z);
	}

	// сложение векторов
	Point3D operator +(Point3D p) const
	{
		return Point3D(x + p.x, y + p.y, z + p.z);
	}

	// длина вектора
	double length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	// Векторное произведение
	Point3D operator ^(Point3D p) const
	{
		return Point3D(det(y, z, p.y, p.z), -det(x, z, p.x, p.z), det(x, y, p.x, p.y));
	}

	// расстояние до точки
	double getDistanceTo(Point3D p) const
	{
		return sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y) + (z - p.z)*(z - p.z));
	}

	// Умножение на скаляр
	Point3D operator *(double p) const
	{
		return Point3D(x * p, y * p, z * p);
	}

	double operator *(Point3D p) const
	{
		return x * p.x + y * p.y + z * p.z;
	}

	double getDistanceToLine(Point3D a, Point3D b) const
	{
		a = a - *this;
		b = b - *this;
		Point3D direction = b - a;
		return (a ^ direction).length() / direction.length();
	}
};

istream &operator >>(istream &in, Point3D &p)
{
	return in >> p.x >> p.y >> p.z;
}

ostream &operator <<(ostream &out, Point3D &p)
{
	return out << p.x << " " << p.y << " " << p.z;
}


#endif
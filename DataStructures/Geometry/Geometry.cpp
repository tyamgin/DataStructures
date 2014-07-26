#pragma comment(linker, "/STACK:500000000") 
#include <functional>
#include <algorithm> 
#include <iostream> 
#include <string.h> 
#include <stdlib.h> 
#include <numeric>
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
typedef pair<int, int> pii;

#if 0

const double Pi = acos(-1.0);

template<typename Type> bool equal(Type a, Type b) {
	return a == b;
}

template<> bool equal(double a, double b) {
	return fabs(a - b) < eps;
}

template<typename Type> int compareTo(Type a, Type b) {
	if (equal(a, b))
		return 0;
	return a < b ? -1 : 1;
}

template<typename Type> struct Point2D;

typedef Point2D<int> PointI;
typedef Point2D<double> Point;

template<typename Type> Type vectorProduct(const Point2D<Type> &a, const Point2D<Type> &b, const Point2D<Type> &c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

template<typename Type> Type determinant(Type a, Type b, Type c, Type d) {
	return a * d - b * c;
}

template<typename Type> bool isOnSegment(const Point2D<Type> &point, const Point2D<Type> &begin, const Point2D<Type> &end) {
	return equal((point.x - begin.x) * (begin.y - end.y), (point.y - begin.y) * (begin.x - end.x));
}

template<typename Type> bool between(Type Left, Type Right, Type x) {
	if (Left > Right)
		swap(Left, Right);
	if (equal(Left, x) || equal(Right, x))
		return true;
	return Left <= x && x <= Right;
}

template<typename Type> struct Point2D {
	Type x, y;

	Point2D(Type x = 0, Type y = 0) : x(x), y(y) {
	}

	bool operator ==(const Point2D &point) const {
		return equal(x, point.x) && equal(y, point.y);
	}

	bool operator <(const Point2D &point) const {
		if (equal(x, point.x))
			return y < point.y;
		return x < point.x;
	}

	Type getDistanceInSquareTo(const Point2D &to) const {
		return (x - to.x) * (x - to.x) + (y - to.y) * (y - to.y);
	}

	double getDistanceTo(const Point2D &to) const {
		return sqrt((double)getDistanceInSquareTo(to));
	}

	Point2D operator -() const {
		return Point(-x, -y);
	}

	void operator -=(const Point2D &point) {
		x -= point.x;
		y -= point.y;
	}

	double length() {
		return sqrt(x * x + y * y + 0.0);
	}

	void normalize() {
		double len = length();
		x /= len;
		y /= len;
	}

	double getDistanceToLine(const Point2D &a, const Point2D &b) {
		double A, B, C;
		getABC(a, b, A, B, C);
		return fabs(A * x + B * y + C) / sqrt(A * A + B * B);
	}

	double getDistanceToSegment(Point2D<Type> a, Point2D<Type> b) {
		if (a == b)
			return getDistanceTo(a);

		a -= *this;
		b -= *this;

		Type A, B, C;
		getABC(a, b, A, B, C);
		double len = sqrt(A * A + B * B + 0.0);
		double h = fabs(C / len);
		Point2D<double> grad(A, B);
		grad.x *= h / len;
		grad.y *= h / len;
		if (between(a.x, b.x, grad.x) && between(a.y, b.y, grad.y) && isOnSegment(grad, a, b) || between(a.x, b.x, -grad.x) && between(a.y, b.y, -grad.y) && isOnSegment(-grad, a, b))
			return h;
		return min(a.length(), b.length());
	}

	friend istream &operator >>(istream &in, Point2D &p) {
		return in >> p.x >> p.y;
	}

	friend ostream &operator <<(ostream &out, Point2D &p) {
		return out << p.x << " " << p.y;
	}
};

template<typename Type> struct Point3D {
	
	Type x, y, z;

	Point3D(Type x = 0, Type y = 0, Type z = 0) : x(x), y(y), z(z) {
		
	}

	Point3D<double> rotated(vector<vector<double> > a) {
		return {
			x * a[0][0] + y * a[1][0] + z * a[2][0],
			x * a[0][1] + y * a[1][1] + z * a[2][1],
			x * a[0][2] + y * a[1][2] + z * a[2][2]
		};
	}

	Point3D<double> rotatedX(double angle) {
		return rotated({ 
			{ 1, 0, 0 }, 
			{ 0, cos(angle), -sin(angle) }, 
			{ 0, sin(angle), cos(angle) } 
		});
	}

	Point3D<double> rotatedY(double angle) {
		return rotated({ 
			{ cos(angle), 0, sin(angle) },
			{ 0, 1, 0 },
			{ -sin(angle), 0, cos(angle) } 
		});
	}

	Point3D<double> rotatedZ(double angle) {
		return rotated({ 
			{ cos(angle), -sin(angle), 0 },
			{ sin(angle), cos(angle), 0 },
			{ 0, 0, 1 } 
		});
	}

	double length() {
		return sqrt(x*x + y*y + z*z);
	}

	Type getDistanceInSquareTo(const Point3D &to) const {
		return (x - to.x)*(x - to.x) + (y - to.y)*(y - to.y) + (z - to.z)*(z - to.z);
	}

	Type getDistanceTo(const Point3D &to) const {
		return sqrt((double)getDistanceInSquareTo(to));
	}

	friend istream &operator >>(istream &in, Point3D &p) {
		return in >> p.x >> p.y >> p.z;
	}

	friend ostream &operator <<(ostream &out, Point3D &p) {
		return out << p.x << " " << p.y << " "<< p.z;
	}

	Point3D operator -(Point3D p) const {
		return Point3D(x - p.x, y - p.y, z - p.z);
	}

	Point3D operator +(Point3D p) const {
		return Point3D(x + p.x, y + p.y, z + p.z);
	}

	// vector product
	Point3D operator ^(Point3D p) const {
		return Point3D(determinant(y, z, p.y, p.z), -determinant(x, z, p.x, p.z), determinant(x, y, p.x, p.y));
	}

	template<typename ByType>
	Point3D operator *(ByType p) const {
		return Point3D(x * p, y * p, z * p);
	}

	Type operator *(Point3D p) const {
		return x * p.x + y * p.y + z * p.z;
	}

	Point3D operator -() const {
		return Point3D(-x, -y, -z);
	}

	double getDistanceToLine(Point3D<double> a, Point3D<double> b) const {
		a = a - *this;
		b = b - *this;
		Point3D<double> direction = b - a;
		Point3D<double> id = direction * (1.0 / direction.length());
		return (-a - id * (-a * id)).length();
	}
};

template<typename Type> void getABC(const Point2D<Type> &a, const Point2D<Type> &b, Type &A, Type &B, Type &C) {
	A = a.y - b.y;
	B = b.x - a.x;
	C = -a.x * A - a.y * B;
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
	double A1 = a.y - b.y;
	double B1 = b.x - a.x;
	double C1 = -a.x * A1 - a.y * B1;

	double A2 = c.y - d.y;
	double B2 = d.x - c.x;
	double C2 = -c.x * A2 - c.y * B2;

	double D = determinant(A1, B1, A2, B2);
	return Point(determinant(-C1, B1, -C2, B2) / D, determinant(A1, -C1, A2, -C2) / D);
}

template<typename Type> struct Polygon : vector<Point2D<Type> > {

	double getDoubleSquare() {
		int i, n = (int)this->size();
		if (n < 3)
			return 0.0;
		double sum1 = sum1 = this->at(0).y * this->at(n - 1).x,
			sum2 = sum2 = this->at(0).x * this->at(n - 1).y;
		for (i = 1; i < n; i++)
			sum1 += this->at(i - 1).x * this->at(i).y;
		for (i = 1; i < n; i++)
			sum2 += this->at(i - 1).y * this->at(i).x;
		return fabs(sum1 - sum2);
	}

	double getSquare() {
		return getDoubleSquare() / 2.0;
	}
};

struct ConvexPolygon : public Polygon<double> {
	bool inPolygon(const Point &p) {
		int n = (int)size(), i;
		vector<int> v(n);
		for (i = 0; i < n; i++) {
			double vc = vectorProduct(at(i), at((i + 1) % n), p);
			v[i] = equal(vc, 0.0) ? 0 : (vc < 0 ? -1 : 1);
		}
		return count(v.begin(), v.end(), -1) == 0 || count(v.begin(), v.end(), 1) == 0;
	}

	double getDistanceTo(Point p) {
		if (inPolygon(p))
			return 0.0;
		double minDistance = p.getDistanceToSegment(at(0), back());
		for (int i = 1; i < (int)size(); i++)
			minDistance = min(minDistance, p.getDistanceToSegment(at(i), at(i - 1)));
		return minDistance;
	}

	ConvexPolygon cut(const Point &a, const Point &b) {
		vector<int> idx;
		ConvexPolygon res(*this);

		for (int i = 0; i < (int)res.size(); i++) {
			Point &cur = res[i];
			Point &next = res[(i + 1) % res.size()];
			double v1 = vectorProduct(a, b, cur);
			double v2 = vectorProduct(a, b, next);
			if ((v1 < 0 && v2 > 0 || v1 > 0 && v2 < 0) && !equal(v1, 0.0) && !equal(v2, 0.0)) {
				Point inter = intersect(cur, next, a, b);
				res.insert(res.begin() + (i + 1) % res.size(), inter);
			}
		}
		for (int i = 0; i < (int)size(); i++) {
			if (isOnSegment(at(i), a, b))
				idx.push_back(i);
		}

		for (int i = 0; i < (int)res.size(); i++) {
			if (vectorProduct(a, b, res[i]) - eps > 0)
				res.erase(res.begin() + i), i--;
		}
		return res;
	}

	ConvexPolygon intersectWith(ConvexPolygon &p) {
		ConvexPolygon res(p);
		for (int i = 0; i < (int)size(); i++)
			res = res.cut(at(i), at((i + 1) % size()));
		return res;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
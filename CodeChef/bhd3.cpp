#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

const int subdivide = 512;
const double step = 1.0 / subdivide;
const double eps = 1e-6;

struct Point {
	double x, y, z;

	bool isZero() const {
		return abs(x) < eps && abs(y) < eps && abs(z) < eps;
	}

	Point operator-(const Point &r) const {
		return Point{x - r.x, y - r.y, z - r.z};
	}

	Point operator+(const Point &r) const {
		return Point{x + r.x, y + r.y, z + r.z};
	}

	bool operator<(const Point &r) const {
		if (x != r.x) return x < r.x;
		if (y != r.y) return y < r.y;
		return z < r.z;
	}

	Point xy() const {
		return Point{x, y, 0};
	}

	double norm2() const {
		return x * x + y * y + z * z;
	}

	Point scale(double factor) const {
		return Point{x * factor, y * factor, z * factor};
	}

	Point unit() const {
		return scale(1.0 / sqrt(norm2()));
	}
};

double dis2(const Point &a, const Point &b) {
	return (a - b).norm2();
}

double sqr(double x) {
	return x * x;
}

struct Donut {
	Point org;
	double R, r;

	bool isIn(const Point &p) const {
		Point pp = p - org;
		if (pp.isZero()) return false;		
		Point pr = pp.xy().unit().scale(R);
		if ((pp - pr).norm2() <= r * r) return true;
		return false;
	}
};

const double pi = 4 * atan(1);

int main () {
	int n;
	scanf("%d", &n);
	double x, y, z;
	double r, R;
	vector<Donut> donuts;
	for (int k = 0; k < n; k++) {
		scanf("%lf%lf%lf%lf%lf", &x, &y, &z, &R, &r);
		donuts.push_back(Donut{Point{x, y, z}, R, r});
	}
	
	double volume = 0;
	for (int kk = 0; kk < (int)donuts.size(); kk++) {
		x = donuts[kk].org.x;
		y = donuts[kk].org.y;
		z = donuts[kk].org.z;
		R = donuts[kk].R;
		r = donuts[kk].r;
		double zmin = floor(z - r);
		double zmax = ceil(z + r);

		for (double k = zmin; k <= zmax; k += step) {
			if (sqr(k - z) > sqr(r)) continue;
			double rdif = sqrt(sqr(r) - sqr(k - z));
			volume += pi * (sqr(R + rdif) - sqr(R - rdif));
		}
	}
	printf("%f\n", volume / subdivide);
	return 0;
}

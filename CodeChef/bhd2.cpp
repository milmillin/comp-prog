#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

const int subdivide = 8;
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

struct Data {
	vector<Donut*> data;

	void add(Donut* x) {
		data.push_back(x);
	}

	long long count(const Point &org) const {
		long long cnt = 0;
		for (int i = 0; i < subdivide; i++) {
			for (int j = 0; j < subdivide; j++) {
				for (int k = 0; k < subdivide; k++) {
					Point test = org + Point{i * step, j * step, k * step};
					for (const auto &d: data) {
						if (d->isIn(test)) {
							cnt++;
							break;
						}
					}
				}
			}
		}
		return cnt;
	}
};

Point di[8] = {Point{0, 0, 0}, Point{0, 0, 1}, Point{0, 1, 0}, Point{0, 1, 1}, Point{1, 0, 0}, Point{1, 0, 1}, Point{1, 1, 0}, Point{1, 1, 1}};

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

	map<Point, Data> mp;

	for (int kk = 0; kk < (int)donuts.size(); kk++) {
		x = donuts[kk].org.x;
		y = donuts[kk].org.y;
		z = donuts[kk].org.z;
		R = donuts[kk].R;
		r = donuts[kk].r;
		int xmax = ceil(x + R + r);
		int ymax = ceil(y + R + r);
		int zmax = ceil(z + r);

		for (int i = floor(x - R - r); i <= xmax; i++) {
			for (int j = floor(y - R - r); j <= ymax; j++) {
				for (int k = floor(z - r); k <= zmax; k++) {
					mp[Point{(double)i, (double)j, (double)k}].add(&donuts[kk]);
				}
			}
		}
	}
	long long volume = 0;
	for (auto &i: mp) {
		volume += i.second.count(i.first);
	}
	printf("%f\n", (double)volume / (subdivide * subdivide * subdivide));
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
	if (a % b == 0) return b;
	return gcd(b, a % b);
}

struct frac {
	long long a, b;

	void reduce() {
		long long g = gcd(a, b);
		a /= g;
		b /= g;
		if (b < 0) {
			a *= -1;
			b *= -1;
		}
	}

	frac(long long _a, long long _b): a(_a), b(_b) {
		reduce();
	}

	frac(long long _a): frac(_a, 1) {}

	frac(): frac(1, 1) {}

	frac operator-(const frac &r) const {
		return frac(r.b * a - r.a * b, b * r.b);
	}

	frac operator*(const frac &r) const {
		return frac(a * r.a, b * r.b);
	}

	void print() const {
		printf("%lld %lld\n", a, b);
	}
};

int n;
frac alpha;

frac aab(int x, int y, int z) {
	if (x < y) {
		if (z < y) return frac(y - 1) * alpha;
		if (z == y) return frac(n) * alpha;
		if (z > y) return frac(1) - (frac(y + 1) * alpha);
	}
	return frac(1) - aab(y - 1, y, z);
}

frac aba(int x, int y, int z) {
	if (x > z) swap(x, z);
	return frac(1) - aab(y - 1, y, x) - aab(y + 1, y, z);
}

void f() {
	int t, x, y, z;
	scanf("%d%d%d%d%d", &n, &t, &x, &y, &z);
	alpha = frac(1, 2 * n + 1);
	if (t == 1) {
		aab(x, y, z).print();
	} else if (t == 2 || t == 4) {
		aba(x, y, z).print();
	} else if (t == 3) {
		aab(z, y, x).print();
	}
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

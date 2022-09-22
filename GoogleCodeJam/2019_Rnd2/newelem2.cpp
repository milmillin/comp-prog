#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct stone {
	int a, b;
};

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

struct cmp {
	int a, b;
	bool gt;

	cmp(int _a, int _b) {
		int g = gcd(_a, _b);
		a = _a / g;
		b = _b / g;
		gt = g < 0;
	}
};

// a / b;
struct frac {
	long long a, b;

	frac(long long _a, long long _b) {
		long long g = gcd(_a, _b);
		a = _a / g;
		b = _b / g;
	}

	frac mul(long long x) const {
		return frac(a * x, b);
	}

	frac operator- (const frac &r) const {
		return frac(a * r.b - r.a * b, b * r.b);
	}

	long long next(long long x) const {
		long long r = a * x / b;
		r++;
		return r;
	}

	long long floor(long long x) const {
		return a * x / b;
	}

	bool operator< (const frac &r) const {
		return (long long)a * r.b < r.a * b;
	}
};

void f() {
	int n;
	scanf("%d", &n);
	vector<stone> tbl(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &tbl[i].a, &tbl[i].b);
	}
	vector<cmp> allcmp;
	allcmp.reserve(n * n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((tbl[i].a == tbl[j].a && tbl[i].b >= tbl[j].b) ||
					(tbl[i].b == tbl[j].b && tbl[i].a >= tbl[j].a)) {
				printf("IMPOSSIBLE\n");
				return;
			}
			if (tbl[i].a == tbl[j].a || tbl[i].b == tbl[j].b) continue;
			allcmp.push_back(cmp(tbl[i].a - tbl[j].a, tbl[j].b - tbl[i].b));
		}
	}

	frac leftBnd(0, 1);
	frac rgtBnd((long long)1e15, 1);

	for (auto &c : allcmp) {
		if (c.gt != (c.b < 0)) {
			rgtBnd = min(rgtBnd, frac(c.a, c.b));
		} else {
			leftBnd = max(leftBnd, frac(c.a, c.b));
		}
	}

	if (!(leftBnd < rgtBnd)) {
		printf("IMPOSSIBLE\n");
		return;
	}

	long long a = 1;
	while (!(frac(leftBnd.next(a), 1) < rgtBnd.mul(a))) {
		a++;
	}
	printf("%lld %lld\n", a, leftBnd.next(a));
}

int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		f();
		fflush(stdout);
	}
	return 0;
}

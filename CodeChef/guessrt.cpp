#include <cstdio>
#include <algorithm>

using namespace std;

const int mod = 1000000007;

inline long long mul(long long x, long long y) {
	return (x * y) % mod;
}

inline long long add(long long x, long long y) {
	return (x + y) % mod;
}

long long poww(long long x, int n) {
	if (n == 0) return 1;
	if (n == 1) return x;
	long long tmp = poww(x, n / 2);
	if (n % 2) {
		return mul(mul(tmp, tmp), x);
	} else {
		return mul(tmp, tmp);
	}
}

long long gcd(long long a, long long b) {
	if (a % b == 0) return b;
	return gcd(b, a % b);
}

// x/y
struct frac {
	long long x, y;

	frac(long long _x, long long _y) {
		x = _x;
		y = _y;
	}

	frac operator+ (const frac &r) const {
		return frac(add(mul(x, r.y), mul(r.x, y)), mul(y, r.y));
	}

	frac operator- (const frac &r) const {
		return frac(add(mul(x, r.y), -mul(r.x, y)), mul(y, r.y));
	}
};

void f() {
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);
	int q = (m + 1) / 2;
	frac ans = frac(1, 1) - frac(poww(n - 1, q), poww(n, q));
	if (m % 2 == 0) {
		ans = ans + frac(poww(n - 1, q), mul(poww(n, q), n + k));
	}
	printf("%lld\n", (mul(ans.x, poww(ans.y, mod - 2)) + mod) % mod);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

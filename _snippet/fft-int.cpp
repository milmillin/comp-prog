#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <cstring>

using namespace std;
using namespace std::complex_literals;

const double pi = 3.14159265358979323846;

#define INT

#ifdef INT
typedef int type;
#else
typedef complex<double> type;
#endif

#ifdef INT
const type C = 7 * 17;
const type K = 23;
const type MOD = (1 << K) * C + 1;

template<typename T>
T mod(T a) {
	if (a <= -MOD) return a % MOD;
	if (a >= MOD) return a % MOD;
	return a;
}

type add(type a, type b) {
	return mod(a + b);
}

type sub(type a, type b) {
	return mod(mod(a - b) + MOD);
}

type mul(type a, type b) {
	return mod(1ll * a * b);
}

type powmod(type a, type b) {
    type res = 1;
    while (b)
        if (b & 1)
            res = mod(res * 1ll * a),  --b;
        else
            a = mod(a * 1ll * a),  b >>= 1;
    return res;
}

type inverse(type a) {
	return powmod(a, MOD - 2);
}

type divide(type a, type b) {
	return (1ll * a * inverse(b)) % MOD;
}

type generator() {
    vector<type> fact;
    type phi = MOD - 1,  n = phi;
    for (type i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back(n);

    for (type res = 2; res <= MOD; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i]) != 1;
        if (ok)  return res;
    }
    return -1;
}

const type R = generator();

type WN[32][2];
type calculate_wn(type logn, bool isInverse) {
	if (WN[logn][isInverse] != -1) return WN[logn][isInverse];
	WN[logn][0] = powmod(R, C * (1 << (K - logn)));
	WN[logn][1] = inverse(WN[logn][0]);
	return WN[logn][isInverse];
}

void init() {
	memset(WN, -1, sizeof(WN));
}
#else

type calculate_wn(int logn, bool isInverse) {
	int n = 1 << logn;
	type asdf = 2.0 * pi * 1i / (double)n;
	if (isInverse) return 1. / exp(asdf);
	return exp(asdf);
}

type add(type a, type b) {
	return a + b;
}

type sub(type a, type b) {
	return a - b;
}

type mul(type a, type b) {
	return a * b;
}

type divide(type a, type b) {
	return a / b;
}

void init() {}
#endif

//swap logn binary bits of i
int indexSwap(int i, int logn) {
	int res = 0;
	while (logn--) {
		res <<= 1;
		res ^= i & 1;
		i >>= 1;
	}
	return res;
}

vector<int> genSwapVector(int logn) {
	int n = 1 << logn;
	vector<type> swapVector(n);
	for (int i = 0; i < n; i++) {
		swapVector[i] = indexSwap(i, logn);
	}
	return swapVector;
}

void fftSwap(vector<type> &a, const vector<int> &swapVector) {
	int n = (int)a.size();
	for (int i = 0; i < n; i++) {
		if (swapVector[i] > i) {
			swap(a[i], a[swapVector[i]]);
		}
	}
}

void transformImpl(vector<type> &a, bool inverse, int logn, int l) {
	int n = 1 << logn;
	if (n == 1) return;

	type wn = calculate_wn(logn, inverse);
	type w = 1;

	transformImpl(a, inverse, logn - 1, l);
	transformImpl(a, inverse, logn - 1, l + (n >> 1));

	type yeven, wyodd;
	for (int k = 0; k < n / 2; k++) {
		yeven = a[l + k];
		wyodd = mul(w, a[l + (n >> 1) + k]);

		a[l + k] = add(yeven, wyodd);
		a[l + (n >> 1) + k] = sub(yeven, wyodd);

		w = mul(w, wn);
	}
}

vector<type> convolution(const vector<type> &y1, const vector<type> &y2) {
	int n = y1.size();

	vector<type> c(n);

	for (int k = 0; k < n; k++) {
		c[k] = mul(y1[k], y2[k]);
	}
	return c;
}

vector<type> multiplyPolynomial(const vector<type> &p1, const vector<type> &p2) {
	int n = (int)p1.size();
	int m = (int)p2.size();

	int logn = 0;
	int sz = 1;
	while (sz < n || sz < m) {
		sz <<= 1;
		logn++;
	}
	sz <<= 1;
	logn++;

	vector<type> t1 = p1;
	vector<type> t2 = p2;
	vector<int> swapVector = genSwapVector(logn);

	t1.resize(sz, 0);
	t2.resize(sz, 0);

	fftSwap(t1, swapVector);
	fftSwap(t2, swapVector);

	transformImpl(t1, false, logn, 0);
	transformImpl(t2, false, logn, 0);

	vector<type> res = convolution(t1, t2);
	fftSwap(res, swapVector);
	transformImpl(res, true, logn, 0);

	res.resize(n + m - 1);

#ifdef INT
	type szInverse = inverse(sz);
#else
	type szInverse = 1. / sz;
#endif

	for (type& i: res) {
		i = mul(i, szInverse);
	}

	return res;
}

int main () {
	init();
	int n, m;
	scanf("%d", &n);
	vector<type> p1(n);
	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		p1[i] = x;
	}
	scanf("%d", &m);
	vector<type> p2(m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &x);
		p2[i] = x;
	}

	vector<type> result = multiplyPolynomial(p1, p2);

	for (int i = 0; i < n + m - 1; i++) {
		//printf("%d ", (int)divide(round(real(result[i])), sz));
		printf("%d ", result[i]);
	}
	printf("\n");
	return 0;
}

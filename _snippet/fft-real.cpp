#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>

using namespace std;
using namespace std::complex_literals;

const double pi = 3.14159265358979323846;

vector<complex<double>> transform(vector<complex<double>> &a) {
	int n = a.size();
	if (n == 1) return a;

	complex<double> asdf = 2.0 * pi * 1i / (double)n;
	complex<double> wn = exp(asdf);
	complex<double> w = 1;

	vector<complex<double>> aeven(n / 2);
	vector<complex<double>> aodd(n / 2);
	
	for (int i = 0; i < n / 2; i++) {
		aeven[i] = a[i * 2];
		aodd[i] = a[i * 2 + 1];
	}

	vector<complex<double>> yeven = transform(aeven);
	vector<complex<double>> yodd = transform(aodd);

	vector<complex<double>> y(n);

	for (int k = 0; k < n / 2; k++) {
		y[k] = yeven[k] + w * yodd[k];
		y[k + n / 2] = yeven[k] - w * yodd[k];
		w *= wn;
	}

	return y;
}

vector<complex<double>> convolution(const vector<complex<double>> &y1, const vector<complex<double>> &y2) {
	int n = y1.size();

	vector<complex<double>> c(n);

	for (int k = 0; k < n; k++) {
		c[k] = y1[k] * y2[k];
	}
	return c;
}

vector<complex<double>> transform_back(vector<complex<double>> &a) {
	int n = a.size();
	if (n == 1) return a;

	complex<double> asdf = 2.0 * pi * 1i / (double)n;
	complex<double> wn = exp(asdf);
	complex<double> w = 1;

	vector<complex<double>> aeven(n / 2);
	vector<complex<double>> aodd(n / 2);
	
	for (int i = 0; i < n / 2; i++) {
		aeven[i] = a[i * 2];
		aodd[i] = a[i * 2 + 1];
	}

	vector<complex<double>> yeven = transform_back(aeven);
	vector<complex<double>> yodd = transform_back(aodd);

	vector<complex<double>> y(n);

	for (int k = 0; k < n / 2; k++) {
		y[k] = yeven[k] + w * yodd[k];
		y[k + n / 2] = yeven[k] - w * yodd[k];
		w /= wn;
	}

	return y;
}

int main () {
	int n, m;
	scanf("%d", &n);
	vector<complex<double>> p1(n);
	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		p1[i] = x;
	}
	scanf("%d", &m);
	vector<complex<double>> p2(m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &x);
		p2[i] = x;
	}

	int sz = 1;
	while (sz < n || sz < m) {
		sz <<= 1;
	}
	sz <<= 1;

	p1.resize(sz, 0);
	p2.resize(sz, 0);

	vector<complex<double>> y1 = transform(p1);
	vector<complex<double>> y2 = transform(p2);

	vector<complex<double>> c = convolution(y1, y2);

	vector<complex<double>> result = transform_back(c);

	for (int i = 0; i < n + m - 1; i++) {
		printf("%d ", (int)round(real(result[i]) / sz));
	}
	printf("\n");
	return 0;
}

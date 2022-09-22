#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int mod = 1000000007;

struct mat {
	vector<vector<long long>> tbl;
	int size;


	mat() {

	}
	mat(int n) {
		tbl.assign(n, vector<long long> (n, 0));
		size = n;
	}	

	mat operator* (const mat &r) const {
		mat tmp(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					tmp.tbl[i][j] += tbl[i][k] * r.tbl[k][j];
					tmp.tbl[i][j] %= mod;
				}
			}
		}			
		return tmp;
	}
	vector<long long>& operator[](int idx) {
		return tbl[idx];
	}

	void print() const {
		for (const auto &i : tbl) {
			for (const auto &j : i) {
				printf("%lld ", j);
			}
			printf("\n");
		}
	}
};

mat tmpp;

mat poww(const mat &b, int x) {
	if (x == 1) return b;
	tmpp = poww(b, x / 2);
	tmpp = tmpp * tmpp;
	if (x%2) return tmpp * b;
	return tmpp;
}

int main () {
	int n, k;
	scanf("%d%d", &n, &k);
	mat ei(2 * k+2);
	ei[0][0] = 1;
	tmpp = mat(2 * k+2);
	for (int i = 1; i <= k; i++) {
		ei[0][i] = 1;
		for (int j = 1; j <= i; j++) {
			ei[j][i] = ei[j - 1][i-1] + ei[j][i-1];
			ei[j][i] %= mod;
		}
	}
	for (int i = 0; i <= k; i++) {
		ei[i][k + i+1] = 1;
		ei[k + i+1][k + i+1] = 1;
	}
	//ei.print();
	long long sum = 0;
	mat eii =poww(ei, n);
	mat init(2 * k +2);
	for (int i = 0; i <= k; i++) {
		init[0][i] = 1;
	}
	init = init * eii;
	//init.print();
	for (int i = k+2; i < 2 * k+2; i++) {
		sum += init[0][i] * (i - k - 1);
		sum %= mod;
	}
	printf("%lld\n", sum);

	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int mod = 1000000007;

struct cell {
	int r, c;

	int st() const {
		return (r + c) % 2;
	}
};

int simulateNeg(int r, int c, cell neg) {
	int st = neg.st();
	vector<vector<int>> tbl(r + 1, vector<int>(c, 0));
	for (int i = 0; i < r; i++) {
		for (int j = (i + st) % 2; j < c; j += 2) {
			int cur = (neg.r == i && neg.c == j);
			if (j - 1 >= 0) cur ^= tbl[i][j - 1];
			if (i - 1 >= 0) cur ^= tbl[i - 1][j];
			if (j + 1 < c) cur ^= tbl[i][j + 1];
			tbl[i + 1][j] = cur;
		}
	}

	int ans = 0;
	for (int j = (r + st + 1) % 2; j < c; j += 2) {
		ans ^= (1 << (j / 2)) * tbl[r][j];
	}
	return ans;
}

int simulate(int r, int c, int st, int k, const vector<vector<int>> &data) {
	vector<vector<int>> tbl(r + 1, vector<int>(c, 0));
	for (int j = (st + 1) % 2; j < c; j += 2) {
		if (k & (1 << (j / 2))) tbl[0][j] = 1;		
	}
	for (int i = 0; i < r; i++) {
		for (int j = (i + st) % 2; j < c; j += 2) {
			int cur = data[i][j];
			if (j - 1 >= 0) cur ^= tbl[i][j - 1];
			if (i - 1 >= 0) cur ^= tbl[i - 1][j];
			if (j + 1 < c) cur ^= tbl[i][j + 1];
			tbl[i + 1][j] = cur;
		}
	}
	int ans = 0;
	for (int j = (r + st + 1) % 2; j < c; j += 2) {
		ans ^= (1 << (j / 2)) * tbl[r][j];
	}
	return ans;
}

/*
void expand(map<int, int> &out, const vector<int> &value) {
	out[0] = 1;
	for (auto i : value) {
		map<int, int> tmp;
		for (auto &j : out) {
			tmp[j.first ^ i] += j.second;
			tmp[j.first ^ i] %= mod;
		}
		for (auto &j : tmp) {
			out[j.first] += j.second;
			out[j.first] %= mod;
		}
	}
}
*/

void expand(vector<int> &out, const vector<int> &value) {
	out[0] = 1;
	for (auto i : value) {
		vector<int> tmp(out.size(), 0);
		for (int j = 0; j < (int)out.size(); j++) {
			tmp[j ^ i] += out[j];
			tmp[j ^ i] %= mod;
		}
		for (int j = 0; j < (int)out.size(); j++) {
			out[j] += tmp[j];
			out[j] %= mod;
		}
	}
}

long long simulateAll(int r, int c, int st, const vector<vector<int>> &data, const vector<int> &way) {
	int k = (st) ? c - c / 2 : c / 2;
	int base = simulate(r, c, st, 0, data);
	vector<int> basis;
	for (int i = 0; i < k; i++) {
		basis.push_back(simulate(r, c, st, 1 << i, data) ^ base);
	}

	k = ((r + st + 1) % 2) ? c / 2: c - c / 2;
	vector<int> cnt(1 << k, 0);
	expand(cnt, basis);

	long long ans = 0;
	for (int i = 0; i < (int)cnt.size(); i++) {
		ans += ((long long)way[i ^ base] * cnt[i]) % mod;
		ans %= mod;
	}
	return ans;
}

void f() {
	int r, c;
	scanf("%d%d", &r, &c);
	vector<vector<int>> data(r, vector<int>(c));
	vector<cell> negs;
	int x;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &data[i][j]);
			if (data[i][j] == -1) {
				negs.push_back(cell{i, j});
				data[i][j] = 0;
			}
		}
	}

	vector<int> basis[2];
	for (auto &neg : negs) {
		basis[neg.st()].push_back(simulateNeg(r, c, neg));
	}

	int a = c / 2;
	int b = c - c / 2;

	if (r % 2) swap(a, b);

	vector<int> way0(1 << a, 0);
	vector<int> way1(1 << b, 0);
	expand(way0, basis[0]);
	expand(way1, basis[1]);

	printf("%lld\n", (simulateAll(r, c, 0, data, way0) * simulateAll(r, c, 1, data, way1)) % mod);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int k[100100];
vector<int> pth[100100];

int t = 0;
int in[100100];
int out[100100];
int tbl[100100];

void dfs(int idx, int par, int d) {
	in[idx] = t++;
	tbl[in[idx]] = d;
	for (auto i : pth[idx]) {
		if (i == par) continue;
		dfs(i, idx, d + 1);
	}
	out[idx] = t;
}

struct bucket {
	vector<int> dis;
	int lazy;
	int left;
	int right;
	bool sortRequired;

	bucket(int _left, int _right): dis(vector<int>(_right - _left)), lazy(0), 
			left(_left), right(_right), sortRequired(false) {
		
		for (int i = left; i < right; i++) {
			dis[i - left] = tbl[i];
		}
		sort(dis.begin(), dis.end());
	}

	int size() {
		return right - left;
	}

	int ask(int x) {
		if (sortRequired) {
			sort(dis.begin(), dis.end());
			sortRequired = false;
		}
		int lo = 0;
		int hi = (int)dis.size();
		int mid;
		while (lo < hi) {
			mid = (lo + hi) >> 1;
			if (dis[mid] <= x - lazy) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
		return (int)dis.size() - lo;
	}

	void update(int l, int r, int val) {
		if (l >= right || r <= left) {
			lazy -= val;
		} else if (l <= left && r >= right) {
			lazy += val;
		} else {
			l = max(l, left);
			r = min(r, right);
			for (int i = left; i < right; i++) {
				if (i >= l && i < r) {
					tbl[i] += val;
				} else {
					tbl[i] -= val;
				}
				dis[i - left] = tbl[i];
			}
			sortRequired = true;
		}
	}
};

vector<bucket> cls;
int sz;

void init(int n) {
	sz = 1000;
	cls.reserve((n - 1) / sz + 1);
	for (int i = 0; i < (n - 1) / sz + 1; i++) {
		cls.push_back(bucket(i * sz, min(n, i * sz + sz)));
	}
}

void update(int l, int r, int val) {
	for (auto &b : cls) {
		b.update(l, r, val);
	}
}

int ask(int idx) {
	int cnt = 0;
	int lo = 0;
	int hi = t - 1;
	int mid;
	while (lo < hi) {
		mid = (lo + hi + 1) >> 1;
		cnt = 0;
		int remain = t;
		for (auto &b : cls) {
			cnt += b.ask(mid);
			if (cnt >= k[idx]) break;
			remain -= b.size();
			if (remain + cnt < k[idx]) break;
		}
		if (cnt >= k[idx]) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}

int ans[100100];

void changeroot(int idx, int par) {
	ans[idx] = ask(idx);
	for (auto i : pth[idx]) {
		if (i == par) continue;
		update(in[i], out[i], -1);
		changeroot(i, idx);
		update(in[i], out[i], 1);
	}
}

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &k[i]);
	}
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		a--;
		b--;
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(0, 0, 0);
	init(n);
	changeroot(0, 0);
	for (int i = 0; i < n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pass;
void passing(int idx, int l, int r, int k) {
	if (k < l || k >= r) return;
	pass.push_back(idx);
	if (l + 1 == r) return;
	int m = (l + r) >> 1;
	passing(idx * 2 + 1, l, m, k);
	passing(idx * 2 + 2, m, r, k);
}

void uniquee(int idx, int l, int r) {
	if (l + 1 == r) return;
}

vector<int> pth[600100];

void clear() {
	for (int i = 0; i < 600100; i++) {
		pth[i].clear();
	}
}

void f() {
	clear();
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		pass.clear();
		passing(0, 0, n, a);
		vector<int> tmp = pass;
		pass.clear();
		passing(0, 0, n, b);
		for (auto u: tmp) {
			for (auto v: pass) {
				pth[u].push_back(v);
				pth[v].push_back(u);
			}
		}
	}
	

}

int main() {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

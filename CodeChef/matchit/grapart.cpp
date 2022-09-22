#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[10100];

vector<int> seg[10100];
int segcnt;

vector<int> part[2];

void check(int idx, int par, bool dep, vector<int> &ss) {
	ss.push_back(idx);
	part[dep].push_back(idx);
	bool same = false;
	for (auto i: pth[idx]) {
		if (i == par) continue;
		if (!same) {
			check(i, idx, !dep, ss);
			same = true;
		} else {
			seg[segcnt].clear();
			segcnt++;
			check(i, idx, !dep, seg[segcnt - 1]);
		}
	}
}

void f() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < 10100; i++) pth[i].clear();
	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		pth[x].push_back(y);
		pth[y].push_back(x);
	}
	segcnt = 0;
	seg[0].clear();
	segcnt++;
	check(1, 1, false, seg[0]);
	int ss = 1;
	if (part[0].size() != part[1].size()) {
		ss++;
		part[0].clear();
		part[1].clear();
		bool cnt = false;
		for (int i = 0; i < segcnt; i++) {
			for (auto j: seg[i]) {
				part[cnt].push_back(j);
				cnt = !cnt;
			}
		}
	}
	printf("%d\n", ss);
	for (auto i: part[0]) {
		printf("%d ", i);
	}
	printf("\n");
	for (auto i: part[1]) {
		printf("%d ", i);
	}
	printf("\n");
	part[0].clear();
	part[1].clear();
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

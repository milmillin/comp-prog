#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct stone {
	int s, e, l;

	int energy (int ti) const {
		return max(e - ti * l, 0);
	}
};

bool operator< (const stone &a, const stone &b) {
	if (a.l * b.s != b.l * a.s) return a.l * b.s > b.l * a.s;
	if (a.l != b.l) return a.l > b.l;
	if (a.s != b.s) return a.s < b.s;
	return a.e > b.e;
}

int calculate(const vector<stone> &tbl) {
	int ti = 0;
	int ans = 0;
	for (auto &s : tbl) {
		ans += s.energy(ti);
		if (s.energy(ti)) ti += s.s;
	}
	return ans;
}

void f() {
	int n;
	scanf("%d", &n);
	vector<stone> tbl;
	tbl.reserve(n);
	int s, e, l;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &s, &e, &l);
		tbl.push_back(stone{s, e, l});
	}

	int ti = s * (n - 1);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int id = -1;
		int cl = 1000000;
		for (int j = 0; j < (int)tbl.size(); j++) {
			if (tbl[j].energy(ti) == 0) continue;
			if (tbl[j].l < cl) {
				cl = tbl[j].l;
				id = j;
			} else if (tbl[j].l == cl && tbl[j].e < tbl[id].e) {
				id = j;
			}
		}
		if (id != -1) {
			ans += tbl[id].energy(ti);
			tbl.erase(tbl.begin() + id);			
		}
		ti -= s;
	}

	printf("%d\n", ans);
	fflush(stdout);
}

int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		f();
	}
	return 0;
}

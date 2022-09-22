#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

pair<int, int> ask(vector<int> &tbl) {
	printf("? ");
	for (auto i: tbl) {
		printf("%d ", i);
	}
	printf("\n");
	fflush(stdout);
	int x, y;
	scanf("%d%d", &x, &y);
	return {x, y};
}

void ans(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

void f() {
	int n;
	scanf("%d", &n);
	vector<int> tbl;
	vector<int> garbage;
	for (int i = 0; i < 5; i++) {
		tbl.push_back(i + 1);
	}
	int cur = 6;
	while (tbl.size() == 5) {
		auto res = ask(tbl);
		garbage.push_back(res.first);
		garbage.push_back(res.second);
		tbl.erase(find(tbl.begin(), tbl.end(), res.first));
		tbl.erase(find(tbl.begin(), tbl.end(), res.second));
		if (cur <= n) tbl.push_back(cur++);
		if (cur <= n) tbl.push_back(cur++);
	}
	fflush(stdout);
	if (tbl.size() == 4) {
		tbl.push_back(garbage.front());
		auto res = ask(tbl);
		garbage.push_back(res.first);
		garbage.push_back(res.second);
		tbl.erase(find(tbl.begin(), tbl.end(), res.first));
		tbl.erase(find(tbl.begin(), tbl.end(), res.second));
	}
	sort(garbage.begin(), garbage.end());
	garbage.resize(unique(garbage.begin(), garbage.end()) - garbage.begin());
	int a = tbl[0];
	int b = tbl[1];
	int c = tbl[2];
	int x = garbage[0];
	int y = garbage[1];
	int z = garbage[2];
	vector<int> tmp;
	tmp = {a, b, x, y, z};
	auto org = ask(tmp);
	tmp = {a, c, x, y, z};
	auto res = ask(tmp);
	if (res.second == org.first) {
		ans(b);
	} else if (res.first == org.second) {
		ans(c);
	} else {
		ans(a);
	}
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
}

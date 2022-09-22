#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
	int n, s;
	scanf("%d%d", &n, &s);
	vector<int> tbl(n);
	vector<vector<int>> pos(100001, vector<int>());
	for (int i = 0; i < n; i++) {
		scanf("%d", &tbl[i]);
		pos[tbl[i]].push_back(i);
	}

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

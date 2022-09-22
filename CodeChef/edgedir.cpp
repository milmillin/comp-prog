#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

struct Edge {
	int to, id;
};

bool flip[100100];
bool indeg[100100];
bool visit[100100];
vector<Edge> pth[100100];

bool solve(int idx) {
	visit[idx] = true;
	bool ans = indeg[idx];
	for (auto &e: pth[idx]) {
		if (visit[e.to]) continue;
		bool res = solve(e.to);
		if (res) {
			flip[e.id] = !flip[e.id];
		}
		ans = (ans != res);
	}
	return ans;
}

void f() {
	for (int i = 0; i < 100100; i++) {
		pth[i].clear();
	}
	memset(flip, 0, sizeof(flip));
	memset(indeg, 0, sizeof(indeg));
	memset(visit, 0, sizeof(visit));

	int n, m;
	scanf("%d%d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		indeg[v] = !indeg[v];
		pth[u].push_back(Edge{v, i});
		pth[v].push_back(Edge{u, i});
	}

	if (m % 2 == 1) {
		printf("-1\n");
		return;
	}

	assert(!solve(1));
	for (int i = 0; i < m; i++) {
		printf("%d ", flip[i]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

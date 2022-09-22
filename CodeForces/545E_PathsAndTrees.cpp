#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
	int to, wgt, idx;
};

vector<edge> pth[300100];

struct ei {
	int idx;
	long long dis;
	int from, wgt;
};

bool operator < (const ei &a, const ei &b) {
	if (a.dis!=b.dis) return a.dis > b.dis;
	return a.wgt > b.wgt;
}

priority_queue<ei> q;
long long dis[300100];

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		pth[a].push_back(edge{b, c, i+1});
		pth[b].push_back(edge{a, c, i+1});
	}
	int x;
	scanf("%d", &x);
	memset(dis, 63, sizeof(dis));
	//dis[x] = 0;
	q.push(ei{x, 0, -1, 0});
	int now, from, wgt;
	long long nowDis;
	long long ans = 0;
	vector<int> ee;
	while (!q.empty()) {
		now = q.top().idx;
		nowDis = q.top().dis;
		from = q.top().from;
		wgt = q.top().wgt;
		q.pop();
		if (dis[now] <= nowDis) continue;
		dis[now] = nowDis;
		ans += wgt;
		if (from != -1) ee.push_back(from);
		for (int i = 0; i < (int)pth[now].size(); i++) {
			if (dis[pth[now][i].to] <= nowDis+pth[now][i].wgt) continue;
//			dis[pth[now][i].to] = nowDis+pth[now][i].wgt;
			q.push(ei{pth[now][i].to, nowDis+pth[now][i].wgt, pth[now][i].idx, pth[now][i].wgt});
		}
	}
	printf("%I64d\n", ans);
	for (int i = 0; i < (int)ee.size(); i++) {
		printf("%d ", ee[i]);
	}
	printf("\n");
	return 0;
}

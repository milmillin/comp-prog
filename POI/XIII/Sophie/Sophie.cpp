#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[1000100];
int deg[1000100];
bool deleted[1000100];
bool selected[1000100];

int cnt[20];

bool work() {
	for (int i = 1; i <= 10; i++) {
		if (cnt[i]) return false;
	}
	return true;
}

void dDeg(int idx) {
	if (deg[idx] == 0) return;
	if (deg[idx] <= 10) {
		cnt[deg[idx]]--;
	}
	deg[idx]--;
	if (deg[idx] <= 10) {

		cnt[deg[idx]]++;
	}
}

void aDeg(int idx) {
	if (deg[idx] <= 10) {
		cnt[deg[idx]]--;
	}
	deg[idx]++;
	if (deg[idx] <= 10) {
		cnt[deg[idx]]++;
	}
}

void dEdge(int u, int v) {
	dDeg(u);
	dDeg(v);
}

void aEdge(int u, int v) {
	aDeg(u);
	aDeg(v);
}

int n, k;
queue<int> q;
deque<int> deq;

int mxk = -2e9;
vector<int> mxlist;
vector<int> dlist;

void solve() {
	if (deq.empty()) return;
	if (k < 0) return;
	//for (auto i : dlist) printf("%d ", i);
	//printf("\n");
	//for (int i = 0; i <= 10; i++) {
		//printf("%d ", cnt[i]);
	//}
	//printf("\n");

	//printf("k %d\n", k);
	//for (auto i : dlist) {
		//printf("%d ", i);
	//}
	//printf("\n");
	vector<int> qqq;
	int top;
	while (true) {
		top = deq.front();
		deq.pop_front();
		qqq.push_back(top);
		if (deq.empty()) {
			while (!qqq.empty()) {
				deq.push_front(qqq.back());
				qqq.pop_back();
			}
			return;
		}
		if (!deleted[top]) break; 
	}
	
	//printf("%d\n\n", top);

	//select top delete adj
	selected[top] = true;
	vector < pair < int, int >> x;
	vector<int> xv;
	for (auto i : pth[top]) {
		if (deleted[i]) continue;
		deleted[i] = true;
		xv.push_back(i);
		dlist.push_back(i);
		k--;
		if (k < 0) break;
		for (auto j : pth[i]) {
			if (deleted[j]) continue;
			dEdge(i, j);
			x.push_back({i, j});
		}
	}
	if (k >= 0) {
		if (work()) {
			//for (auto i : dlist) printf("%d ", i);
			//printf("\n");
			if (k>mxk) {
				mxk = k;
				mxlist = dlist;
			}
		}
		//printf("s1\n");
		solve();
	}
	for (auto i : xv) {
		dlist.pop_back();
		deleted[i] = false;
		k++;
	}
	for (auto &i : x) {
		aEdge(i.first, i.second);
	}
	selected[top] = false;
	//printf("yay\n");

	//delete top 
	deleted[top] = true;
	k--;
	x.clear();
	for (auto i : pth[top]) {
		if (deleted[i]) continue;
		dEdge(top, i);
		x.push_back({top, i});
	}
	dlist.push_back(top);
	
	if (k >= 0) {
		if (work()) {
			if (k > mxk) {
				mxk = k;
				mxlist = dlist;
			}
		}
		//printf("s2\n");
		solve();
	}

	dlist.pop_back();
	for (auto &i : x) {
		aEdge(i.first, i.second);
	}
	deleted[top] = false;
	k++;

	while (!qqq.empty()) {
		deq.push_front(qqq.back());
		qqq.pop_back();
	}
}

bool ddd[1000100];

int main () {
	scanf("%d%d", &n, &k);
	k = n - k;
	int m;
	scanf("%d", &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		sort(pth[i].begin(), pth[i].end());
		pth[i].resize(unique(pth[i].begin(), pth[i].end()) - pth[i].begin());
		deg[i] = pth[i].size();
		if (deg[i] <= 10) cnt[deg[i]]++;
		if (deg[i] > k) q.push(i);
	}
	//printf("----- %d\n", k);
	int top;
	while (!q.empty()) {
		top = q.front();
		q.pop();
		if (deg[top] <= k) continue;
		deleted[top] = true;
		dlist.push_back(top);
		k--;
		if (k < 0) break;

		for (auto i : pth[top]) {
			if (deleted[i]) continue;
			dEdge(top, i);
			if (deg[i] > k) q.push(i);
		}
	}
	if (k < 0) {
		printf("NIE\n");
		return 0;
	}
	if (work()) {
		if (k > mxk) {
			mxk = k;
			mxlist = dlist;
		}
		//printf("%d\n", n - dlist.size());
		//for (int i = 1; i <= n; i++) {
			//if (!deleted[i]) printf("%d ", i);
		//}
		//printf("\n");
		//return 0;
	}
	for (int i = 1; i <= n; i++) {
		if (deleted[i]) continue;
		if (deg[i] == 0) selected[i] = true;
		else {
			deq.push_back(i);
			//printf(" + %d\n", i);
		}
	}
	//for (int i = 0; i <= 10; i++) {
		//printf("%d ", cnt[i]);
	//}
	//printf("\n");
	solve();
	if (mxk == -2e9) {
		printf("NIE\n");
		return 0;
	}
	printf("%d\n", n-mxlist.size());
	for (auto i : mxlist) {
		ddd[i] = true;
		//printf("%d ", i);
	}
	//printf("\n");
	for (int i = 1; i <= n; i++) {
		if (!ddd[i]) printf("%d ", i);
	}
	printf("\n");
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

int val[100100];
vector<int> pth[100100];

int t;
int dis[100100];
int low[100100];
vector<int> stk;
bool instk[100100];

int compCnt;
int compOf[100100];
vector<int> compVal[100100];
vector<int> compPth[100100];

void scc(int idx) {
	dis[idx] = low[idx] = t++;
	stk.push_back(idx);
	instk[idx] = true;

	for (auto i : pth[idx]) {
		if (dis[i] == -1) {
			scc(i);
			low[idx] = min(low[idx], low[i]);
		} else if (instk[i]) {
			low[idx] = min(low[idx], dis[i]);
		}
	}

	if (low[idx] == dis[idx]) {
		compVal[compCnt].clear();
		compPth[compCnt].clear();

		while (stk.back() != idx) {
			compOf[stk.back()] = compCnt;
			compVal[compCnt].push_back(val[stk.back()]);
			instk[stk.back()] = false;
			stk.pop_back();
		}

		compOf[stk.back()] = compCnt;
		compVal[compCnt].push_back(val[stk.back()]);
		instk[stk.back()] = false;
		stk.pop_back();

		sort(compVal[compCnt].begin(), compVal[compCnt].end());
		compCnt++;
	}
}

//long long dp[100002][201];
vector<vector<long long>> dp;
const int mod = 1000000021;

long long ei(int idx, int k);

long long solve(int idx, int k) {
	if (k == -1) return 0;
	if (dp[idx][k] != -1) return dp[idx][k];
	long long mx = solve(idx, k - 1);
	int limit = min(k, (int)compVal[idx].size() - 1);
	for (int toThis = 0; toThis <= limit; toThis++) {
		int toThat = k - toThis;
		long long sum = (long long)compVal[idx][toThis] * ((int)compVal[idx].size() - toThis);
		mx = max(mx, sum + ei(idx, toThat));
	}
	return dp[idx][k] = mx;
}

vector<vector<long long>> dp2;

long long ei(int idx, int k) {
	if (dp2[idx][k] != -1) return dp2[idx][k];
	long long mx = 0;
	for (auto i : compPth[idx]) {
		mx = max(mx, solve(i, k));
	}
	return dp2[idx][k] = mx;
}


void f() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		pth[i].clear();
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		pth[a].push_back(b);
	}
	t = 0;
	memset(dis, -1, sizeof(dis));
	memset(low, 0, sizeof(low));
	compCnt = 0;
	for (int i = 1; i <= n; i++) {
		if (dis[i] == -1) {
			scc(i);
			assert(stk.empty());
		}
	}
	for (int i = 1; i <= n; i++) {
		for (auto j : pth[i]) {
			if (compOf[i] == compOf[j]) continue;
			compPth[compOf[i]].push_back(compOf[j]);
		}
	}
	for (int i = 0; i < compCnt; i++) {
		sort(compPth[i].begin(), compPth[i].end());
		compPth[i].resize(unique(compPth[i].begin(), compPth[i].end()) - compPth[i].begin());
	}

	//memset(dp, -1, sizeof(dp));
	dp = vector<vector<long long>>(n + 1, vector<long long>(k + 1, -1));
	dp2 = vector<vector<long long>>(n + 1, vector<long long>(k + 1, -1));
	long long ans = 0;
	//for (int kk = 0; kk <= k; kk++) {
		for (int i = 0; i < compCnt; i++) {
			ans = max(ans, solve(i, k));
		}
	//}
	printf("%lld\n", ans % mod);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

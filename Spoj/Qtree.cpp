#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct edge {
	int to, wgt, ord;
};

int n;
vector<edge> pth[10010];

int cost[10010];
int ord[10010];
int epos[10010];

int par[20][10010];
int sc[10010];
int dep[10010];

int seg[40010];
int base[10010];

int chainNo[10010];
int pos[10010];

struct chain {
	int head;
	int len;
	int st;
};

chain chains[10010];

void dfs(int idx, int p, int d) {
	sc[idx] = 1;
	par[0][idx] = p;
	dep[idx] = d;
	for (auto &i : pth[idx]) {
		if (i.to == p) continue;
		cost[i.to] = i.wgt;
		ord[i.to] = i.ord;
		dfs(i.to, idx, d + 1);
		sc[idx] += sc[i.to];
	}
	//return sc[idx]=s;
}

int curChain = 0;
int curPos = 0;

void hld(int ch, int idx, int p) {
	chain &cur = chains[ch];
	chainNo[idx] = ch;
	pos[idx] = curPos++;
	//assert(pos[idx] < 10010);
	base[pos[idx]] = cost[idx];
	epos[ord[idx]] = pos[idx];

	if (cur.len == 0) {
		cur.head = idx;
		cur.st = pos[idx];
	}
	//cur.end = pos[idx] + 1;
	cur.len++;

	int s = -1;
	int aa = 0;
	for (auto &i : pth[idx]) {
		if (i.to == p) continue;
		if (sc[i.to] > aa) {
			s = i.to;
			aa = sc[i.to];
		}	
	}

	if (s != -1) {
		hld(ch, s, idx);
	} else {
		assert(sc[idx] == 1);
	}
	for (auto &i : pth[idx]) {
		if (i.to == p) continue;
		if (i.to == s) continue;
		hld(curChain++, i.to, idx);
	}
}

void build(int idx, int l, int r) {
	if (l + 1 == r) {
		seg[idx] = base[l];
		return;
	}
	int m = (l + r) >> 1;
	build(idx * 2 + 1, l, m);
	build(idx * 2 + 2, m, r);
	seg[idx] = max(seg[idx * 2 + 1], seg[idx * 2 + 2]);
}

void update(int idx, int l, int r, int k) {
	if (k < l||k >= r) return;
	if (l + 1 == r) {
		seg[idx] = base[l];
		return;
	}
	int m = (l + r) >> 1;
	update(idx * 2 + 1, l, m, k);
	update(idx * 2 + 2, m, r, k);
	seg[idx] = max(seg[idx * 2 + 1], seg[idx * 2 + 2]);
}

int query(int idx, int l, int r, int ll, int rr) {
	if (rr <= l||ll >= r) return - 2e9;
	if (ll <= l&&rr >= r) return seg[idx];
	int m = (l + r) >> 1;
	return max(query(idx * 2 + 1, l, m, ll, rr), query(idx * 2 + 2, m, r, ll, rr));	
}

int lca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	int dif = dep[a] - dep[b];
	for (int i = 19; i >= 0; i--) {
		if ((dif >> i) & 1) a = par[i][a];
	}
	if (a == b) return a;
	for (int i = 19; i >= 0; i--) {
		if (par[i][a] != par[i][b]) {
			a = par[i][a];
			b = par[i][b];
		}
	}			
	return par[0][a];
}

int query_up(int lo, int hi) {
	if (lo == hi) return 0;
	//int mx = 0;
	//while (true) {
		//if (lo == hi) return mx;
		//if (chainNo[lo] == chainNo[hi]) {
			//return max(mx,query(0, 0, curPos, pos[hi] + 1, pos[lo] + 1));
		//}
		//mx = max(mx, query(0, 0, curPos, chains[chainNo[lo]].st, pos[lo] + 1));
		//lo = par[0][chains[chainNo[lo]].head];
	//}
	if (chainNo[lo] == chainNo[hi]) {
		//assert(pos[hi] <= pos[lo]);
		return query(0, 0, curPos, pos[hi] + 1, pos[lo] + 1);
	}
	int tmp = query_up(par[0][chains[chainNo[lo]].head], hi);
	return max(query(0, 0, curPos, chains[chainNo[lo]].st, pos[lo] + 1), tmp);
}

char buf[30];

void f() {
	for (int i = 0; i < 10010; i++) {
		pth[i].clear();
	}
	memset(cost, 0, sizeof(cost));
	memset(par, 0, sizeof(par));
	memset(sc, 0, sizeof(sc));
	memset(ord, 0, sizeof(ord));
	memset(epos, 0, sizeof(epos));
	memset(seg, 0, sizeof(seg));
	memset(base, 0, sizeof(base));
	memset(chainNo, 0, sizeof(chainNo));
	memset(pos, 0, sizeof(pos));
	memset(chains, 0, sizeof(chains));
	
	curChain = 0;
	curPos = 0;

	scanf("%d", &n);
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		pth[a].push_back(edge{b, c, i});
		pth[b].push_back(edge{a, c, i});
	}
	dfs(1, 1, 1);
	hld(curChain++, 1, 1);
	build(0, 0, curPos);

	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			par[j][i] = par[j - 1][par[j - 1][i]];
		}
	}
	while (true) {
		scanf("%s", buf);
		if (buf[0] == 'C') {
			scanf("%d%d", &a, &b);
			base[epos[a]] = b;
			update(0, 0, curPos, epos[a]);
		} else if (buf[0] == 'Q') {
			scanf("%d%d", &a, &b);
			c = lca(a, b);
			//printf("--%d\n", c);
			printf("%d\n", max(query_up(a, c), query_up(b, c)));
		} else {
			break;
		}
	}
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

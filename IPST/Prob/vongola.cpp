#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long mon[100100];
vector<int> pth[100100];

int dep[100100];

int in[100100];
int out[100100];
int pos[100100];

struct node {
	int idx;
	long long mon;
	int time;
};

bool operator < (const node &a, const node &b) {
	return a.time < b.time;
}

vector<node> ei[100100];

int t=0;
void dfs(int idx, int p, int d) {
	in[idx] = t++;
	pos[in[idx]] = idx;
	dep[idx] = d;
	ei[d].push_back(node{idx, 0, in[idx]});
	for (auto i : pth[idx]) {
		dfs(i,idx,d+1);
	}
	out[idx] = t;
}

int main () {
	int n, q;
	scanf("%d%d", &n,&q);
	int a, b;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		if (a != -1) {
			pth[a].push_back(i);
		}
		mon[i] = b;
	}
	dfs(0, 0, 0);
	int c;
	for (int i = 0; i < q; i++) {
		scanf("%d%d%d", &a, &b, &c);
		auto &xx = ei[dep[a] + b];
		auto lo = lower_bound(xx.begin(), xx.end(), node{0, 0, in[a]});
		auto hi = upper_bound(xx.begin(), xx.end(), node{0, 0, out[a] - 1});
		mon[a] -= (long long)(hi - lo) * c;
		lo->mon += c;
		if (hi!=xx.end()) hi->mon -= c;
	}	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < ei[i].size(); j++) {
			if (j) ei[i][j].mon += ei[i][j - 1].mon;
			mon[ei[i][j].idx] += ei[i][j].mon;
		}	
	}
	for (int i = 0; i < n; i++) {
		printf("%lld\n", mon[i]);
	}
	return 0;
}

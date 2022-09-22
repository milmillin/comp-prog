#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std; 

vector<int> par[100100];
vector<int> pth[100100];
int col[100100];

bool use[10];
bool work;

int other(int a, int b) {
	if (a != 1 && b != 1) return 1;
	if (a != 2 && b != 2) return 2;
	return 3;
}

int other(int a) {
	if (a != 1) return 1;
	if (a != 2) return 2;
	return 3;
}

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	if (n == 1) {
		printf("1\n1\n");
		return 0;
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		par[b].push_back(a);
		pth[a].push_back(b);
	}
	for (int i = 1; i < n; i++) {
		pth[i].push_back(i + 1);
		par[i + 1].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		sort(pth[i].begin(), pth[i].end());
		sort(par[i].begin(), par[i].end());
	}
	col[1] = 1;
	col[2] = 2;
	for (int i = 1; i <= n; i++) {
		//printf("--%d\n", i);
		if (col[i] == 0) {
			for (int j = 1; j <= 3; j++) use[j] = false;
			for (auto j : par[i]) {
				use[col[j]] = true;	
				//printf("%d %d\n", j, col[j]);
			}
			work = false;
			for (int j = 1; j <= 3; j++) {
				if (use[j]) continue;
				col[i] = j;
				work = true;
				break;
			}
			assert(work);
		}
		int tmp = pth[i].size() - 1;
		for (int j = tmp - 1; j >=0; j--) {
			a = pth[i][j];
			b = pth[i][j + 1];
			auto tmp = lower_bound(par[b].begin(), par[b].end(),a);	
			if (tmp == par[b].end()) continue;
			if (*tmp != a) continue;
			//printf("yay %d %d\n",a,b);
			if (col[a] == 0 && col[b] == 0) col[a] = other(col[i]);
			if (col[a] > 0) col[b] = other(col[a], col[i]);
			else if (col[b] > 0) col[a] = other(col[b], col[i]);
			//printf("%d %d\n", col[a], col[b]);
		}
	}
	int mx = 2;
	for (int i = 1; i <= n; i++) {
		mx = max(mx, col[i]);
	}
	printf("%d\n", mx);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", col[i]);
	}
	return 0;
}

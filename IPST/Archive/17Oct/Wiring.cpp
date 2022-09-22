#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

vector<int> pth[100100];
int indeg[100100];
int tbl[100100];

void f() {
	int n;
	scanf("%d",&n);
	int a,b;
	
	for (int i=1;i<=n;i++) {
		pth[i].clear();
		indeg[i]=0;
		scanf("%d",&tbl[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&a);
		if (a==tbl[i]) continue;
		if (a&&tbl[i]) {
			pth[a].push_back(tbl[i]);
			indeg[tbl[i]]++;
		}
	}
	queue<int> q;
	for (int i=1;i<=n;i++) {
		if (!indeg[i]) q.push(i);
	}
	vector<int> ans;
	int now;
	while (!q.empty()) {
		now = q.front();
		q.pop();
		ans.push_back(now);
		//printf("%d\n",now);
		for (int i=0;i<pth[now].size();i++) {
			indeg[pth[now][i]]--;
			if (!indeg[pth[now][i]]) q.push(pth[now][i]);
		}
	}
	if (ans.size()==n) printf("YES\n");
	else printf("NO\n");
	return;
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

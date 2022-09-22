#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

vector<int> pth[100100];
int indeg[100100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		indeg[b]++;
	}
	queue<int> q;
	for (int i=1;i<=n;i++) {
		if (indeg[i]==0) q.push(i);
	}
	int now;
	vector<int> ans;
	while (!q.empty()) {
		now = q.front();
		ans.push_back(now);
		q.pop();
		for (int i=0;i<(int)pth[now].size();i++) {
			indeg[pth[now][i]]--;
			if (indeg[pth[now][i]]==0) q.push(pth[now][i]);
		}
	}
	if ((int)ans.size()!=n) {
		printf("no\n");
	} else {
		for (int i=0;i<n;i++) {
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}

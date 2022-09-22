#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int m[30];
int l[30];
int r[30];

vector<int> pth[30];
int indeg[30];

int main () {
	int n,c;
	scanf("%d%d",&n,&c);
	for (int i=0;i<c;i++) {
		scanf("%d%d%d",&m[i],&l[i],&r[i]);
	}
	int maxx=(1<<c)-1;
	for (int i=0;i<=maxx;i++) {
	//	printf("%d\n",i);
		memset(indeg,0,sizeof(indeg));
		for (int j=1;j<=n;j++) {
			pth[j].clear();
		}
		for (int j=0;j<c;j++) {
			if ((1<<j)&i) {
				pth[r[j]].push_back(m[j]);
				indeg[m[j]]++;
				pth[m[j]].push_back(l[j]);
				indeg[l[j]]++;
			} else {
				pth[l[j]].push_back(m[j]);
				indeg[m[j]]++;
				pth[m[j]].push_back(r[j]);
				indeg[r[j]]++;
			}
		} 
		queue<int> q;
		vector<int> ans;
		for (int j=1;j<=n;j++) {
			if (indeg[j]==0) q.push(j);
		}
		int now;
		while (!q.empty()) {
			now = q.front();
			//printf("--%d\n",now);
			q.pop();
			ans.push_back(now);
			/*
			for (int j=0;j<pth[now].size();j++) {
				indeg[pth[now][j]]--;
				if (!indeg[pth[now][j]]) q.push(pth[now][j]);
			}
			*/
			/*
			for (int k=0;k<pth[now].size();k++) {
				indeg[pth[now][k]]--;
				if (!indeg[pth[now][k]]) q.push(pth[now][k]);
			}
			*/
		}
		if (ans.size()==n) {
			printf("YES\n");
			for (int j=0;j<n;j++) {
				printf("%d ",ans[j]);
			}
			printf("\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}

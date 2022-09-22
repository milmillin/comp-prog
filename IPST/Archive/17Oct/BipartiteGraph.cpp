#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

bool f() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<vector<int> > pth(n+1);
	vector<int> color(n+1,0);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	queue<int> q;
	for (int j=1;j<=n;j++) {
		if (color[j]) continue;
		q.push(j);
		color[j]=1;
		int now;
		while (!q.empty()) {
			now = q.front();
			q.pop();
			for (int i=0;i<pth[now].size();i++) {
				if (color[pth[now][i]]) {
					if (color[pth[now][i]]==color[now]) return false;
					continue;
				}
				if (color[now]==1) {
					color[pth[now][i]]=2;
					q.push(pth[now][i]);
				} else {
					color[pth[now][i]]=1;
					q.push(pth[now][i]);
				}
			}
		}
	}
	return true;
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) printf("%s\n",(f())?"yes":"no");
	return 0;
}

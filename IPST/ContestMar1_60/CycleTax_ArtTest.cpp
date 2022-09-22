#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[1010];

bool visit[1010];
int low[1010];
int dis[1010];
int timee=1;
bool hasArt;

void dfs(int idx,int p) {
	//printf("%d\n",idx);
	dis[idx]=timee++;
	low[idx]=dis[idx];
	visit[idx]=true;
	for (auto i:pth[idx]) {
		if (i==p) continue;
		if (visit[i]) {
			//printf("//%d\n",i);
			low[idx]=min(low[idx],dis[i]);
			continue;
		}
		dfs(i,idx);
		low[idx]=min(low[idx],low[i]);
		if (low[i]>=dis[idx]) {
			//printf("--%d\n",idx);
			if (idx==1) continue;
			hasArt=true;
		}
	}
	//printf("** %d %d %d\n",idx,dis[idx],low[idx]);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	hasArt=false;
	dfs(1,1);
	assert(!hasArt);	
	//printf("%d\n",hasArt);
	return 0;

}

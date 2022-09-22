#include <cstdio>
#include <queue>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[1010];
int qs[20];
int ans[1010];
int dis[1010];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	assert(n<=1000);
	for (int i=0;i<k;i++) {
		scanf("%d",&qs[i]);
		//qs.push_back(x);
	}	
	//printf("yay\n");
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	queue<int> q;
	for (int i=1;i<=n;i++) {
		memset(dis,63,sizeof(dis));
		dis[i]=0;
		ans[dis[i]]++;
		q.push(i);
		//printf("** %d\n",i);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			//printf("%d\n",now);
			for (auto j:pth[now]) {
				//printf("-- %d\n",j);
				if (dis[j]<=dis[now]+1) continue;
				dis[j]=dis[now]+1;
				ans[dis[j]]++;
				q.push(j);
			}
		}	
	}	
	for (int i=0;i<k;i++) {
		printf("%d\n",ans[qs[i]]);
	}
	return 0;
}

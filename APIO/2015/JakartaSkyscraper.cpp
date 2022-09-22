#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

vector<int> pth[30100];
int dis[30100];

struct ei {
	int x,dis;
};

bool operator< (const ei &a, const ei &b) {
	return a.dis>b.dis;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	int s,t;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		if (i==0) s=a;
		if (i==1) t=a;
	}
	for (int i=0;i<n;i++) {
		sort(pth[i].begin(),pth[i].end());
		pth[i].erase(unique(pth[i].begin(),pth[i].end()),pth[i].end());
	}
	memset(dis,63,sizeof(dis));
	dis[s]=0;
	priority_queue<ei> q;
	q.push(ei{s,0});
	int now,nowdis;
	while (!q.empty()) {
		now = q.top().x;
		nowdis = q.top().dis;
		q.pop();
		if (dis[now]<nowdis) continue;
		if (now==t) {
			printf("%d\n",dis[now]);
			return 0;
		}
		for (auto p:pth[now]) {
			for (int i=1;now+i*p<n;i++) {
				if (dis[now+i*p]<=nowdis+i) continue;
				dis[now+i*p]=nowdis+i;
				q.push(ei{now+i*p,nowdis+i});
			}
			for (int i=1;now-i*p>=0;i++) {
				if (dis[now-i*p]<=nowdis+i) continue;
				dis[now-i*p]=nowdis+i;
				q.push(ei{now-i*p,nowdis+i});
			}
		}
	}
	printf("-1\n");
	return 0;
}

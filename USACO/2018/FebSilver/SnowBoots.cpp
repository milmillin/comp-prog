#include <cstdio>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

int f[1000];
int d[1000];
int tbl[1000];

int dis[1000];

struct ei {
	int num;
	int idx;
};

bool operator< (const ei &a, const ei &b) {
	return a.num>b.num;
}

priority_queue<ei> qq;

int main () {
	freopen("snowboots.in","r",stdin);
	freopen("snowboots.out","w",stdout);
	int n,b;
	scanf("%d%d",&n,&b);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	for (int i=0;i<b;i++) {
		scanf("%d%d",&f[i],&d[i]);
	}
	memset(dis,63,sizeof(dis));
	dis[0]=0;
	qq.push(ei{0,0});
	ei now;
	while (!qq.empty()) {
		now = qq.top();
		qq.pop();
		//printf("%d %d\n",now.num,now.idx);
		//bool pushed=false;
		if (now.idx==n-1) break;
		while (now.num<b) {
			//printf("-- %d\n",now.num);
			if (tbl[now.idx]>f[now.num]) {
				now.num++;
				continue;
			}
			for (int i=1;i<=d[now.num];i++) {
				if (now.idx+i>=n) break;
				if (tbl[now.idx+i]>f[now.num]) continue;	
				if (dis[now.idx+i]<=now.num) continue;
				dis[now.idx+i]=now.num;
				qq.push(ei{now.num,now.idx+i});
				//pushed=true;
			}
			now.num++;
		}
	}
	printf("%d\n",dis[n-1]);
	return 0;
}

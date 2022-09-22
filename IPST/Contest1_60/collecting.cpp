#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int ord[50100];

struct ei {
	int to,wgt;
};

vector<ei> pth[50100];

struct pp {
	int now,dis,ord;
};

bool operator< (const pp &a, const pp &b) {
	return a.dis>b.dis;
}

int dis[40][50100];
priority_queue<pp> q;

int main () {
	int n,m,l;
	scanf("%d%d%d",&n,&m,&l);
	int s,t;
	scanf("%d%d",&s,&t);
	for (int i=1;i<=n;i++) {
		scanf("%d",&ord[i]);
	}
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(ei{b,c});
	}
	memset(dis,63,sizeof(dis));
	dis[0][s]=0;
	q.push(pp{s,0,0});
	int now,nowDis,nowOrd;
	int nextOrd,nextDis;
	while (!q.empty()) {
		now=q.top().now;
		nowDis=q.top().dis;
		nowOrd=q.top().ord;
		q.pop();
		if (nowDis>dis[nowOrd][now]) continue;
		for (auto &j:pth[now]) {
			if (ord[j.to]==nowOrd+1) nextOrd=nowOrd+1;
			else nextOrd=nowOrd;
			nextDis=nowDis+j.wgt;
			if (dis[nextOrd][j.to]<=nextDis) continue;
			dis[nextOrd][j.to]=nextDis;
			q.push(pp{j.to,nextDis,nextOrd});
		}
	}
	printf("%d\n",dis[ord[t]][t]);
	return 0;
}

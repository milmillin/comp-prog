#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct road {
	int to,idx;
};

vector<road> pth[300100];
int dis[300100];
bool use[300100];

struct ei {
	int idx, dis;
};

queue<ei> q;

int main () {
	int n,k,d;
	scanf("%d%d%d",&n,&k,&d);
	vector<int> police(k);
	int x;
	memset(dis,63,sizeof(dis));
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		dis[x]=0;
		q.push(ei{x,0});
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(road{b,i});
		pth[b].push_back(road{a,i});
	}
	int now,nowDis;
	while (!q.empty()) {
		now = q.front().idx;
		nowDis = q.front().dis;
		q.pop();
		for (int i=0;i<(int)pth[now].size();i++) {
			if (dis[pth[now][i].to]<=nowDis+1) continue;
			dis[pth[now][i].to]=nowDis+1;
			use[pth[now][i].idx]=true;
			q.push(ei{pth[now][i].to,nowDis+1});
		}
	}
	int cnt=0;
	for (int i=1;i<n;i++) {
		if (!use[i]) cnt++;
	}
	printf("%d\n",cnt);
	for (int i=1;i<n;i++) {
		if (!use[i]) {
			printf("%d ",i);
		}
	}
	printf("\n");
	return 0;
}

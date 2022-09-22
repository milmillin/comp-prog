#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct ei {
	int dis,idx;
};

bool operator<(const ei &a, const ei &b) {
	return a.dis>b.dis;
}

int tbl[1000100];
int dd[1000100];

priority_queue<ei> q;

int main () {
	int n;
	
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(dd,63,sizeof(dd));
	q.push(ei{0,1});
	int now,nowDis;
	while (!q.empty()) {
		now=q.top().idx;
		nowDis=q.top().dis;
		dd[now]=nowDis;
		q.pop();
		//printf("%d %d\n",now,nowDis);
		if (now+1<=n) {
			if (nowDis+1<dd[now+1]) {
				dd[now+1]=nowDis+1;
				//printf("--%d %d\n",nowDis+1,now+1);
				q.push(ei{nowDis+1,now+1});
			}
		}
		//printf("%d\n",now+tbl[now]);
		if (now+tbl[now]<=n) {
			//printf("yay\n");
			if (nowDis+1>=dd[now+tbl[now]]) continue;
			dd[now+tbl[now]]=nowDis+1;
			//printf("++%d %d\n",nowDis+1,now+tbl[now]);
			q.push(ei{nowDis+1,now+tbl[now]});
		}
	}
	printf("%d\n",dd[n]);
	return 0;
}

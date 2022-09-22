#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

struct edge {
	int to,wgt;
};

struct qq {
	int idx,id,sz;
};

bool operator<(const qq &a, const qq &b) {
	if (a.sz!=b.sz) return a.sz<b.sz;
	return a.id>b.id;
}

vector<edge> pth[200100];
int sz[200100];
int id[200100];
priority_queue<qq> q;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&sz[i]);
		if (sz[i]) {
			q.push(qq{i,i,sz[i]});
		}
		id[i]=i;
	}
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
		pth[b].push_back(edge{a,c});
	}
	while (!q.empty()) {
		a=q.top().idx;
		b=q.top().id;
		c=q.top().sz;
		q.pop();
		//printf("%d %d %d\n",a,b,c);
		if (c>sz[b]) {
			sz[b]=c;
			id[b]=a;
		} else if (c==sz[b]) {
			if (a<id[b]) {
				id[b]=a;
			}
		} else continue;
		for (int i=0;i<(int)pth[b].size();i++) {
			if (c-pth[b][i].wgt<sz[pth[b][i].to]) continue;
			q.push(qq{a,pth[b][i].to,c-pth[b][i].wgt});
			//printf("+ %d %d %d\n",a,pth[b][i].to,c-pth[b][i].wgt);
		}
	}
	for (int i=1;i<=n;i++) {
		printf("%d %d\n",(sz[i])?id[i]:0,sz[i]);
	}
	return 0;
}

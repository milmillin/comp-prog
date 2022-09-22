#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct edge {
	int from,to,wgt;
};

bool operator<(const edge &a, const edge &b) {
	return a.wgt>b.wgt;
}

vector<edge> ee;
vector<int> pth[200100];
int col[200100];

struct eew {
	int id;
};

bool operator<(const eew &a, const eew &b) {
	return ee[a.id].wgt>ee[b.id].wgt;
}

bool inQueue[200100];
priority_queue<eew> qq;

int main () {
	freopen("grass.in","r",stdin);
	freopen("grass.out","w",stdout);
	int n,m,k,q;
	scanf("%d%d%d%d",&n,&m,&k,&q);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		ee.push_back(edge{a,b,c});
		pth[a].push_back(ee.size()-1);
		pth[b].push_back(ee.size()-1);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&col[i]);
	}
	for (int i=0;i<m;i++) {
		if (col[ee[i].from]!=col[ee[i].to]) {
			inQueue[i]=true;
			qq.push(eew{i});
		}
	}
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		col[a]=b;
		for (int i=0;i<(int)pth[a].size();i++) {
			if (col[ee[pth[a][i]].from]!=col[ee[pth[a][i]].to]&&!inQueue[pth[a][i]]) qq.push(eew{pth[a][i]});
		}
		while (!qq.empty()&&col[ee[qq.top().id].from]==col[ee[qq.top().id].to]) {
			inQueue[qq.top().id]=false;
			qq.pop();
		}
		printf("%d\n",ee[qq.top().id].wgt);
	}
	
	return 0;
}

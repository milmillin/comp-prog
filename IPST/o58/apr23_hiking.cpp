#include <cstdio>
#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct edge {
	int to,comp;
	edge* rev;
};

vector<edge*> pth[100100];
int lo[100100];
int di[100100];
int ti=0;
bool visit[100100];
bool isArt[100100];

vector<edge*> stk;

int curComp=0;

void dfs(int x,int p) {
	di[x]=lo[x]=ti++;
	visit[x]=true;
	for (auto &i:pth[x]) {
		if (i->to==p) continue;
		stk.push_back(i);
		if (visit[i->to]) {
			lo[x]=min(lo[x],di[i->to]);
			continue;
		}
		dfs(i->to,x);
		lo[x]=min(lo[x],lo[i->to]);
		if (lo[i->to]>=di[x]) {
			isArt[i->to]=true;
			curComp++;
			while (stk.back()!=i) {
				stk.back()->comp=curComp;
				stk.back()->rev->comp=curComp;
				//printf("-- %d %d %d\n",stk.back()->to,stk.back()->rev->to,curComp);
				stk.pop_back();
			}
			stk.back()->comp=curComp;
			stk.back()->rev->comp=curComp;
			stk.pop_back();
		}
	}
}

int dis[100100];
int par[100100];
int parComp[100100];
queue<int> q;

int main () {
	int n,m,l;
	scanf("%d%d%d",&n,&m,&l);
	int a,b;

	edge *ab,*ba;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		ab=new edge{b,0};
		ba=new edge{a,0};
		
		ab->rev=ba;
		ba->rev=ab;

		pth[a].push_back(ab);
		pth[b].push_back(ba);
	}
	dfs(1,1);

	memset(dis,63,sizeof(dis));
	dis[1]=0;
	par[1]=1;
	q.push(1);
	int now;
	while (!q.empty()) {
		now = q.front();
		q.pop();
		for (auto i:pth[now]) {
			if (dis[i->to]<=dis[now]+1) continue;
			par[i->to]=now;
			parComp[i->to]=i->comp;
			dis[i->to]=dis[now]+1;
			q.push(i->to);
		}
	}
	vector<int> res;
	int cur=par[n];
	int cComp=parComp[n];
	while (par[cur]!=cur) {
		if (parComp[cur]!=cComp) {
			assert(parComp[cur]!=0);
			res.push_back(dis[cur]);
		}
		//if (isArt[cur]) res.push_back(dis[cur]);
		cComp=parComp[cur];
		cur=par[cur];
	}
	if (res.empty()) {
		printf("0\n");
		return 0;
	}
	reverse(res.begin(),res.end());
	int cnt=1;
	int left=res.front();
	for (auto i:res) {
		if (i-left>2*l) {
			cnt++;
			left=i;
		}
	}
	printf("%d\n",cnt);
	return 0;
}

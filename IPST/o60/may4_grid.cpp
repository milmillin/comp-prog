#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> pth[10010];
int deg[10010];
bool used[10010];

int dis[10010];
int par[10010];

int grid[200][200];

pair<int,int> loc[10010];

bool solve(int w,int h,int pw,int c0) {
	grid[0][0]=c0;
	grid[w-1][0]=pw;
	used[c0]=true;
	used[pw]=true;
	int cur=par[pw];
	int cc=1;
	while (par[cur]) {
		grid[w-cc-1][0]=cur;	
		used[cur]=true;
		cur=par[cur];
		cc++;
	}
	bool chk;
	for (int j=0;j<h-1;j++) {
		for (int i=0;i<w;i++) {
			chk=false;
			for (auto k:pth[grid[i][j]]) {
				if (used[k]) continue;
				chk=true;
				grid[i][j+1]=k;
				used[k]=true;
			}
			if (!chk) return false;
		}
	}
	return true;
}

int main () {
	int w,h,m;	
	scanf("%d%d%d",&w,&h,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	vector<int> candid;
	int n=w*h;
	for (int i=1;i<=n;i++) {
		if (deg[i]>2) continue;
		for (auto j:pth[i]) {
			if (deg[j]==3) {
				candid.push_back(i);
				break;
			}
		}
	}
	//printf("%d\n",candid.size());
	queue<int> q;
	int now;
	int maxdis;
	vector<int> corner;
	for (auto c:candid) {
		memset(dis,-1,sizeof(dis));
		dis[c]=0;
		q.push(c);
		maxdis=0;
		while (!q.empty()) {
			now = q.front();
			q.pop();
			for (auto i:pth[now]) {
				if (dis[i]!=-1) continue;
				dis[i]=dis[now]+1;
				q.push(i);
			}
			maxdis=max(maxdis,dis[now]);
		}	
		//printf("-- %d\n",maxdis);
		if (maxdis==w+h-2) {
			corner.push_back(c);
		}
	}
	//printf("%d\n",corner.size());
	assert(corner.size()==4);
	memset(dis,-1,sizeof(dis));
	q.push(corner[0]);
	dis[corner[0]]=0;
	while (!q.empty()) {
		now=q.front();
		q.pop();
		//printf("** %d\n",now);
		for (auto i:pth[now]) {
			//printf("**** %d %d\n",i,dis[i]);
			if (dis[i]!=-1) continue;
			dis[i]=dis[now]+1;
			par[i]=now;
			q.push(i);
		}
	}
	//for (auto i:corner) printf("ccc %d\n",i);
	int pw,ph,pwh;
	pw=ph=pwh=-1;
	for (int i=1;i<4;i++) {
		//printf("-- %d\n",dis[corner[i]]);
		if (dis[corner[i]]==w-1) {
			if (pw==-1) pw=corner[i];
			else ph=corner[i];
		}
		else if (dis[corner[i]]==h-1) ph=corner[i];
		else pwh=corner[i];
	}	
	assert(pw!=-1&&ph!=-1&&pwh!=-1);

	bool swp=false;
	if (!solve(w,h,pw,corner[0])) {
		memset(used,false,sizeof(used));
		solve(h,w,ph,corner[0]);
		swp=true;
		swap(w,h);
	}

	for (int i=0;i<w;i++) {
		for (int j=0;j<h;j++) {
			if (swp) loc[grid[i][j]]={j,i};
			else loc[grid[i][j]]={i,j};
		}
	}
	for (int i=1;i<=w*h;i++) {
		printf("%d %d\n",loc[i].first,loc[i].second);
	}
	return 0;
}

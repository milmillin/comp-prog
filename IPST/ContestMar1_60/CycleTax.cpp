#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[1010];
int visit[1010];
bool work[1010][1010];
bool ww[1010];
int ma,mb;
int dep[1010];

vector<int> pth2[1010];

bool dfs(int idx,int p,int d) {
	printf("%d %d\n",p,idx);
	visit[idx]=true;
	dep[idx]=d;
	if (idx==mb) {
		return ww[idx]=true;
	}	
	bool w=false;
	bool tmp;
	for (auto i:pth[idx]) {
		if (i==p) continue;
		if (visit[i]) {
			if (dep[i]>dep[idx]) continue;
			//if (ww[i]==0) continue;
			//if (i==mb) w=true;
			printf("end %d %d\n",i,ww[i]);
			w=w||(ww[i]==1);
			work[idx][i]=(ww[i]==1);
			work[i][idx]=(ww[i]!=1);
			continue;
		}
		tmp=dfs(i,idx,d+1);
		w=w||tmp;
		work[idx][i]=tmp;
		work[i][idx]=!tmp;
	}
	return ww[idx]=w;
}

bool visit2[1010];
bool dfs_test(int idx,int org) {
	//printf("%d\n",idx);
	visit2[idx]=true;
	bool w=false;
	for (auto i:pth2[idx]) {
		//printf("-- %d\n",i);
		if (visit2[i]) {
			//printf("ff\n");
			if (i==org) w=true;
			continue;
		}
		w=w||dfs_test(i,org);
	}
	//visit2[idx]=false;
	return w;
}

vector<pair<int,int>> tbl;

int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c;
	int mn=2e9;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(b);
		pth[b].push_back(a);
		tbl.push_back({a,b});
		if (c<mn) {
			mn=c;
			ma=a;
			mb=b;
		}
	}
	//memset(ww,-1,sizeof(ww));
	dfs(ma,mb,1);	
	//assert(false);
	for (int i=1;i<=n;i++) assert(visit[i]);
	work[ma][mb]=false;
	work[mb][ma]=true;
	printf("%d 1\n",mn);
	for (auto &i:tbl) {
		//assert(work[i.first][i.second]!=work[i.second][i.first]);
		if (work[i.first][i.second]) {
			printf("%d %d ",i.first,i.second);
			pth2[i.first].push_back(i.second);
		} else {
			printf("%d %d ",i.second,i.first);
			pth2[i.second].push_back(i.first);
		}
		if (min(i.first,i.second)==min(ma,mb)&&max(i.first,i.second)==max(ma,mb)) {
			printf("1\n");
		} else {
			printf("0\n");
		}
	}

	for (int i=1;i<=n;i++) {
		memset(visit2,0,sizeof(visit2));
		assert(dfs_test(i,i));
		//printf("yay %d\n",i);
	}
	return 0;
}

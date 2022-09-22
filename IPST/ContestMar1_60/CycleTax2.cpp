#include <cstdio>

using namespace std;

bool adj[1010][1010];
bool work[1010][1010];
int ma,mb;
int n,m;

bool visit[1010];
int dis[1010];

bool dfs(int idx,int p) {
	visit[idx]=true;
	if (idx==mb) return true;	
	bool w=false;
	bool tmp;
	for (int i=1;i<=n;i++) {
		if (i==p) continue;
		if (visit[idx]) continue;
		tmp=dfs(i,idx);
		w=w||dfs(i,idx);	
	}
}

int main () {
	scanf("%d%d",&n,&m);
	int a,b,c;
	int mn=2e9;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		adj[a][b]=adj[b][a]=true;
		if (c<mn) {
			mn=c;
			ma=a;
			mb=b;
		}
	}
	adj[ma][mb]=adj[mb][ma]=false;
	work[mb][ma]=true;
	return 0;
}

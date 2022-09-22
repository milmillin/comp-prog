#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int par[20][100100];
int mn[20][100100];
int dep[100100];
vector<int> pth[100100];

void dfs(int idx,int d) {
	dep[idx]=d;
	for (auto i:pth[idx]) {
		dfs(i,d+1);
	}
}

int lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	//printf("** %d %d %d\n",a,b,dif);
	for (int i=0;i<20;i++) {
		if ((1<<i)&dif) a=par[i][a];
	}
	//printf("** %d %d %d\n",a,b,dif);
	if (a==b) return a;
	for (int i=19;i>=0;i--) {
		//printf("aa %d %d\n",i,par[i][a]);
		if (par[i][a]!=par[i][b]) {
			a=par[i][a];
			b=par[i][b];
			//printf("!!! %d %d\n",a,b);
		}
	}
	return par[0][a];
}

int query_up(int idx,int dp) {
	int mnn=2e9;
	for (int i=0;i<20;i++) {
		if ((1<<i)&dp) {
			mnn=min(mnn,mn[i][idx]);
			idx=par[i][idx];
		}
	}
	return mnn;
}

int query(int a,int b) {
	int c=lca(a,b);
	//printf("lca %d\n",c);
	return min(query_up(a,dep[a]-dep[c]),query_up(b,dep[b]-dep[c]));
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		par[0][i]=a;
		mn[0][i]=b;
		pth[a].push_back(i);
	}
	for (int i=1;i<20;i++) {
		for (int j=0;j<n;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
			mn[i][j]=min(mn[i-1][j],mn[i-1][par[i-1][j]]);
		}
	}
	dfs(0,1);
	int q,k,m,a1,a2;
	scanf("%d%d%d%d%d",&q,&k,&m,&a1,&a2);
	int ri;
	for (int i=0;i<q;i++) {
		//printf("--%d %d\n",a1,a2);
		ri=query(a1,a2);	
		if (ri==2e9) ri=0;
		printf("%d\n",ri);
		a1=a2;
		a2=((a2*k+ri)%m)%n;
	}
	return 0;
}

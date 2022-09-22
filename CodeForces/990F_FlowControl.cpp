#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[200100];

int par[200100];

int findpar(int x) {
	if (par[x]==x) return x;
	return par[x]=findpar(par[x]);
}

struct edge {
	int a,b,id;
};

struct ee {
	int to,id,sign;
};

vector<ee> pth[200100];

int ans[200100];

int dfs(int x,int p) {
	//printf("++ %d\n",x);
	int sum=tbl[x];	
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		//printf("-- %d\n",i.id);
		//
		ans[i.id]=dfs(i.to,x);
		sum+=ans[i.id];
		ans[i.id]*=i.sign;
	}
	return sum;
}

int main () {
	int n;	
	scanf("%d",&n);
	int sum=0;
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		sum+=tbl[i];
		par[i]=i;
	}	
	if (sum==0) {
		printf("Possible\n");
	} else {
		printf("Impossible\n");
		return 0;
	}
	vector<edge> ed;
	int m;
	int a,b;
	scanf("%d",&m);
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		ed.push_back(edge{a,b,i});
	}
	for (auto &e:ed) {
		if (findpar(e.a)==findpar(e.b)) continue;
		pth[e.a].push_back(ee{e.b,e.id,1});
		pth[e.b].push_back(ee{e.a,e.id,-1});
		par[findpar(e.a)]=findpar(e.b);
	}	
	//printf("yay\n");
	dfs(1,1);
	for (int i=0;i<m;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

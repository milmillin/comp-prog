#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct edge {
	int a,b,c;
};

bool operator< (const edge &a, const edge &b) {
	return a.c<b.c;
}

int pp[100100];

struct ei {
	int to,w;
};

vector<ei> pth[100100];

int findpar(int x) {
	if (pp[x]==x) return x;
	return pp[x]=findpar(pp[x]);
}

int par[20][100100];
int w[100100];
long long subsize[100100];
int tbl[100100]; 
int dep[100100];

struct newedge {
	int a,b;
};

void inittree(int x,int p) {
	subsize[x]=tbl[x];
	dep[x]=dep[p]+1;
	for (auto i:pth[x]) {
		if (i.to==p) continue;
		par[0][i.to]=x;
		w[i.to]=i.w;
		inittree(i.to,x);
		subsize[x]+=subsize[i.to];
	}
}

//int lca(int a,int b) {
	//if (dep[a]<dep[b]) swap(a,b);
	//int dif=dep[a]-dep[b];
	//for (int i=0;i<20;i++) {
		//if (dif&(1<<i)) a=par[i][a];
	//}
	//if (a==b) return a;
	//for (int i=19;i>=0;i--) {
		//if (par[i][a]!=par[i][b]) {
			//a=par[i][a];
			//b=par[i][b];
		//}
	//}
	//return par[0][a];
//}

bool mark[200100];
int lca(int a,int b) {
	//printf("%d %d\n",a,b);
	memset(mark,false,sizeof(mark));
	while (par[0][a]!=a) {
		mark[a]=true;
		a=par[0][a];
	}	
	mark[a]=true;
	while (par[0][b]!=b) {
		if (mark[b]) return b;
		b=par[0][b];
	}
	if (mark[b]) return b;
	//printf("yay\n");
	assert(false);
	return -1;
}

vector<newedge> ned;
long long ans;

vector<int> stk;

void disconnect(int a,int b) {
	subsize[b]-=subsize[a];
	par[0][a]=a;
	w[a]=0;
}

void makeroot(int a) {
	if (par[0][a]==a) return;
	makeroot(par[0][a]);
	subsize[par[0][a]]-=subsize[a];
	subsize[a]+=subsize[par[0][a]];

	w[par[0][a]]=w[a];
	w[a]=0;

	par[0][par[0][a]]=a;	
	par[0][a]=a;
}

bool use[100100];
void connect(int a,int b,int wgt) {
	//make sure a is root
	makeroot(a);
	par[0][a]=b;			
	w[a]=wgt;
	subsize[b]+=subsize[a];
}

void solve(int id) {
	if (id==ned.size()) {
		//printf("yay\n");
		long long candid=0;
		for (auto i:stk) {
			//printf("-- %d\n",i);
			candid+=subsize[i]*w[i];
		}
		ans=max(ans,candid);
		return;
	}
	//not add id
	solve(id+1);
	//add id
	
	//find max in cycle
	newedge e=ned[id];	
	int a=e.a;
	int b=e.b;
	int c=lca(a,b);
	int mida=-1;
	int ma=0;
	int midb=-1;
	int mb=0;
	vector<pair<int,int>> changing;
	while (a!=c) {
		if (use[a]) {
			changing.push_back({a,w[a]});
			a=par[0][a];
			continue;
		}
		if (w[a]>ma) {
			ma=w[a];
			mida=a;
		}
		a=par[0][a];
	}
	while (b!=c) {
		if (use[b]) {
			changing.push_back({b,w[b]});
			b=par[0][b];
			continue;
		}
		if (w[b]>mb) {
			mb=w[b];
			midb=b;
		}
		b=par[0][b];
	}
	if (mida==-1&&midb==-1) return;
	int m,n,x,y;
	if (mb<ma) {
		//b ontop a
		y=e.b;
		x=e.a;
		m=mida;
		n=par[0][mida];
	} else {
		//a ontop b
		y=e.a;
		x=e.b;
		m=midb;
		n=par[0][midb];
	}
	int tmp=w[m];
	int to=max(ma,mb);
	for (auto &ii:changing) {
		w[ii.first]=to;	
	}
	disconnect(m,n);
	connect(x,y,to);
	stk.push_back(x);
	use[x]=true;
	solve(id+1);
	use[x]=false;
	stk.pop_back();
	disconnect(x,y);
	connect(m,n,tmp);
	for (auto &ii:changing) {
		w[ii.first]=ii.second;
	}
}

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int a,b,c;
	vector<edge> ed;
	ed.reserve(m);
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		ed.push_back(edge{a,b,c});
	}
	sort(ed.begin(),ed.end());
	for (int i=1;i<=n;i++) pp[i]=i;
	for (auto &e:ed) {
		if (findpar(e.a)!=findpar(e.b)) {
			pth[e.a].push_back(ei{e.b,e.c});	
			pth[e.b].push_back(ei{e.a,e.c});
			pp[findpar(e.a)]=findpar(e.b);
		} else continue;
	}
	ned.reserve(k);
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		ned.push_back(newedge{a,b});
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	par[0][1]=1;
	inittree(1,1);
	//for (int i=0;i<20;i++) {
		//for (int j=1;j<=n;j++) {
			//par[i][j]=par[i-1][par[i-1][j]];
		//}
	//}
	//for (int i=1;i<=n;i++) {
		//printf("%lld\n",subsize[i]);
	//}
	solve(0);
	//for (int i=1;i<=n;i++) {
		//printf("%lld\n",subsize[i]);
	//}
	//printf("--\n");
	printf("%lld\n",ans);
	return 0;
}

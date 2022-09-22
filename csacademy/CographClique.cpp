#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int tbl[500];

bool adj[2][500][500];

struct graph {
	vector<int> vert;
	bool inv;

	bool hasEdge(int u,int v) const {
		return adj[inv][u][v];
	}

	graph(): inv(0) {}
	graph(vector<int> v,bool i): vert(v), inv(i) {}
};

void findconnected(int x,const graph &G,vector<bool> &visit,graph &out) {
	for (auto i:G.vert) {
		if (!G.hasEdge(x,i)) continue;
		if (visit[i]) continue;
		visit[i]=true;
		out.vert.push_back(i);
		findconnected(i,G,visit,out);
	}
}

struct answer {
	int sum;
	vector<int> vert;

	bool operator< (const answer &r) const {
		return sum<r.sum;
	}

	answer operator+ (const answer &r) const {
		answer tmp;
		tmp.sum=sum+r.sum;
		tmp.vert=vert;
		tmp.vert.insert(tmp.vert.end(),r.vert.begin(),r.vert.end());
		return tmp;
	}
};

int n,m;
answer findmaxclique(graph &G) {
	if (G.vert.size()==1) return answer{tbl[G.vert[0]],{G.vert[0]}};
	vector<bool> visit(n+1,false);
	answer mx{0,{}};
	for (auto v:G.vert) {
		if (visit[v]) continue;
		visit[v]=true;
		//C: connected component in G
		graph C;
		C.inv=G.inv;
		C.vert.push_back(v);
		findconnected(v,G,visit,C);	
		
		//Ci: inverse of C
		graph Ci(C.vert,!C.inv);
		vector<bool> visit2(n+1,false);

		answer sum{0,{}};
		for (auto u:Ci.vert) {
			if (visit2[u]) continue;
			visit2[u]=true;
			//D: connected component in Ci then invert
			graph D;
			D.vert.push_back(u);
			findconnected(u,Ci,visit2,D);
			D.inv=C.inv;
			
			sum=sum+findmaxclique(D);
		}		
		mx=max(mx,sum);
	}
	return mx;
}

int main () {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		adj[0][a][b]=adj[0][b][a]=true;
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			if (i==j) continue;
			adj[1][i][j]=!adj[0][i][j];
		}
	}
	graph G;
	for (int i=1;i<=n;i++) {
		G.vert.push_back(i);
	}

	answer ans=findmaxclique(G);
	printf("%d\n",ans.sum);
	printf("%d\n",ans.vert.size());
	for (auto i:ans.vert) {
		printf("%d ",i);
	}
	printf("\n");
	return 0;
}

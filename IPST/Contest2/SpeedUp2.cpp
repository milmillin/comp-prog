#include <cstdio>
#include <vector>

using namespace std;

struct edge {
	int idx,wgt;
};

struct ei {
	int idx;
	long long wgt;
	int lev,last;
};

bool operator< ()

long long dis[80010];
vector<edge> pth[80010];

int main () {
	int n,m,l,k;
	scanf("%d%d%d%d",&n,&m,&l,&k);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
	}
	memset(dis,63,sizeof(dis));
	
	return 0;
}

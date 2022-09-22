#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;


vector<int> pth[100100];
int deg[100100];

struct node {
	vector<int> chd;
};

node nodes[100100];
vector<int> npth[100100];

void dfs(int x,int p) {	
	for (auto i:pth[x]) {
		if (i==p) continue;
		if (deg[i]==1) {
			nodes[x].chd.push_back(i);
		} else {
			npth[x].push_back(i);
			dfs(i,x);
		}
	}
}

int k;
int mic[100100][20];
int mod=10007;

int dp(int x) {
						
}


int main () {
	int n,m;
	scanf("%d%d%d",&n,&m,&k);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	int root=-1;
	for (int i=1;i<=m+n;i++) {
		if (deg[i]>1) root=1;
		assert(deg[i]<=3);
	}
	assert(root!=-1);
	dfs(root,root);
	

	return 0;
}

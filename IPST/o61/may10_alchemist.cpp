#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[1010];
int dep[1010];
int mxdep=0;

void dfs(int x,int d) {
	dep[x]=d;
	mxdep=max(mxdep,d);
	for (auto i:pth[x]) {
		dfs(i,d+1);
	}
}

int tbl[1010][100];

int cur[100];

int main () {
	int n,m,k,q;
	scanf("%d%d%d%d",&n,&m,&k,&q);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[b].push_back(a);
	}	
	dfs(0,0);	
	//printf("---\n");
	//for (int i=0;i<n;i++) {
		//printf("%d ",dep[i]);
	//}
	//printf("\n---\n");
	int nn;
	int x;
	for (int i=0;i<m;i++) {
		scanf("%d",&nn);
		for (int j=0;j<nn;j++) {
			scanf("%d",&x);
			tbl[i][dep[x]]++;
		}
	}
	//printf("---\n");
	for (int i=0;i<q;i++) {
		scanf("%d",&nn);
		memset(cur,0,sizeof(cur));
		for (int j=0;j<nn;j++) {
			scanf("%d",&x);
			for (int ii=0;ii<=mxdep;ii++) {
				cur[ii]+=tbl[x][ii];
			}	
		}
		//for (int j=0;j<=mxdep;j++) {
			//printf("%d ",cur[j]);
		//}
		//printf("\n");
		bool print=false;
		for (int j=mxdep;j>0;j--) {
			if (cur[j]%2) {
				printf("%d\n",mxdep-j);
				print=true;
				break;
			}
			cur[j-1]+=cur[j]/2;
			cur[j]=0;
		}
		if (!print) {
			printf("%d\n",mxdep);
		}
	}
	return 0;
}

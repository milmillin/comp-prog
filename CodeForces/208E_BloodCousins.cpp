#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> chd[100100];
int par[100100];
int sz[100100];
int num[100100];
int height[100100];
vector<int> numWhgt[100100];
int cnt=1;

int recur(int idx,int hgt) {
	num[idx]=cnt;
	numWhgt[hgt].push_back(cnt);
	height[idx]=hgt;
	cnt++;
	int now=1;
	for (int i=0;i<chd[idx].size();i++) {
		now+=recur(chd[idx][i],hgt+1);
	}
	return sz[idx]=now;
}
/*
int getPar(int v,int r) {
	if (r==1) return par[v];
	if (memPar.count(make_pair(v,r))) return memPar[make_pair(v,r)];
	return memPar[make_pair(v,r)]=getPar(par[v],r-1);
}
*/
vector<int> root;

int parr[100100][20];

int main () {
	int n;
	scanf("%d",&n);
	int x;
	par[0]=0;
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		if (x) {
			chd[x].push_back(i);
			par[i]=x;
		} else root.push_back(i);
		parr[i][0]=par[i];
	}

	for (int i=0;i<root.size();i++) {
		recur(root[i],1);
	}

	for (int j=1;j<20;j++) {
		for (int i=1;i<=n;i++) {
			parr[i][j]=parr[parr[i][j-1]][j-1];
		}
	}

	int m;
	scanf("%d",&m);
	int v,r;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&v,&r);
		//v=getPar(v,r);
		int org=v;

		for (int i=20;i>=0;i--) {
			if ((1<<i)>r) continue;
			else {
				v=parr[v][i];
				r-=(1<<i);
			}
		}

		if (v) {
			int from = num[v];
			int to = num[v]+sz[v]-1;

			int start = lower_bound(numWhgt[height[org]].begin(),numWhgt[height[org]].end(),from)-numWhgt[height[org]].begin();
			int endd = upper_bound(numWhgt[height[org]].begin(),numWhgt[height[org]].end(),to)-numWhgt[height[org]].begin();
			printf("%d ",endd-start-1);

			//printf("%d ",recur(v,r)-1);
		} else {
			printf("0 ");
		}
	}
	printf("\n");
	return 0;
}

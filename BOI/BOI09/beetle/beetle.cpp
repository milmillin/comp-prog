#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int ml[310][310][310];
int mr[310][310][310];

int tbl[310];
int n,m;

int r(int i,int j,int k);

int l(int i,int j,int k) {
	if (k==0) return 0;
	if (ml[i][j][k]!=-1) return ml[i][j][k];
	ml[i][j][k]=1e9;
	if (i) {
		ml[i][j][k]=min(ml[i][j][k],l(i-1,j,k-1)+k*(tbl[i]-tbl[i-1]));
	}	
	if (j<n-1) {
		ml[i][j][k]=min(ml[i][j][k],r(i,j+1,k-1)+k*(tbl[j+1]-tbl[i]));
	}
	return ml[i][j][k];
} 

int r(int i,int j,int k) {
	if (k==0) return 0;
	if (mr[i][j][k]!=-1) return mr[i][j][k];
	mr[i][j][k]=1e9;
	if (i) {
		mr[i][j][k]=min(mr[i][j][k],l(i-1,j,k-1)+k*(tbl[j]-tbl[i-1]));
	}
	if (j<n-1) {
		mr[i][j][k]=min(mr[i][j][k],r(i,j+1,k-1)+k*(tbl[j+1]-tbl[j]));
	}
	return mr[i][j][k];
}

int main () {
	scanf("%d%d",&n,&m);
	bool haszero=false;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		if (tbl[i]==0) haszero=true;
	}
	if (!haszero) n++;
	sort(tbl,tbl+n);
	int zero=-1;
	for (auto i=0;i<n;i++) {
		if (tbl[i]==0) {
			zero=i;
			break;
		}
	}
	memset(ml,-1,sizeof(ml));
	memset(mr,-1,sizeof(mr));
	int ans=0;
	for (int i=1;i<n;i++) {
		ans=max(ans,i*m-l(zero,zero,i));
	}
	if (haszero) ans+=m;
	printf("%d\n",ans);
	return 0;
}

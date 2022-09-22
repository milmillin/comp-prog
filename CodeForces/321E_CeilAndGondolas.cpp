#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[4010][4010];

int mic[1000][4010];

void solve(int d,int l,int r,int ll,int rr) {
	if (l>=r) return;
	int m=(l+r)>>1;
	mic[d][m]=2e9;
	int id=-1,tmp;
	for (int i=ll;i<min(rr,m+1);i++) {
		tmp=mic[d-1][i]+tbl[m][m]-tbl[i][m]-tbl[m][i]+tbl[i][i];
		if (mic[d][m]>tmp) {
			mic[d][m]=tmp;
			id=i;
		}
	}
	if (l+1==r) return;
	solve(d,l,m,ll,id+1);
	solve(d,m+1,r,id,rr);
}

int n,m;

void scan() {
	for(int i = 1 ; i<= n ; i++){
		for(int j = 1 ; j<= n ; j++){
			char ch = '$';
			while(!isdigit(ch)){
				ch = getchar();
			}
			tbl[i][j] = ch-'0';
			tbl[i][j]+=tbl[i-1][j]+tbl[i][j-1]-tbl[i-1][j-1];
		}
	}
}
int main () { 

	scanf("%d%d",&n,&m);
	scan();
	//memset(mic,-1,sizeof(mic));
	for (int i=1;i<=n;i++) {
		mic[1][i]=tbl[i][i];
	}
	for (int i=2;i<=m;i++) {
		solve(i,1,n+1,1,n+1);
	}
	printf("%d\n",mic[m][n]/2);
	return 0;
}

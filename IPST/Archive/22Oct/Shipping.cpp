#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int tbl[100100];
vector<int> pth[100100];
int mx[100100][4][5]; //1stMax <-0 3-> 4thMax
int mxId[100100][4][5];

void pushMx(int *tblA,int *tblB,int idx,int val) {
	//a.push_back(make_pair(val,idx));
	tblA[4]=val;
	tblB[4]=idx;
	for (int i=3;i>=0;i--) {
		if (tblA[i]<tblA[i+1]) {
			swap(tblA[i],tblA[i+1]);
			swap(tblB[i],tblB[i+1]);
		} else break;
	}
}

void f() {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		pth[i].clear();
	}
	memset(mx,-1,sizeof(mx));
	memset(mxId,-1,sizeof(mxId));
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	int ans=-1;
	for (int i=0;i<4;i++) {
		for (int j=1;j<=n;j++) {
			for (int k=0;k<(int)pth[j].size();k++) {
				if (i==0) {
					pushMx(mx[j][i],mxId[j][i],pth[j][k],tbl[pth[j][k]]);
				} else {
					for (int l=0;l<2;l++) {
						if (mxId[pth[j][k]][i-1][l]==j) continue;
						pushMx(mx[j][i],mxId[j][i],pth[j][k],mx[pth[j][k]][i-1][l]);
					}
				}
			}
			//printf("%d ",mx[j][i][0].first);
			if (i==3) {
				if (mx[j][i][0]==-1) continue;
				ans=max(ans,mx[j][i][0]+tbl[j]);
			}
		}
		//printf("\n");
	}
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

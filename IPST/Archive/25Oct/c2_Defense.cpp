#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[3010];
int minn[3010];
int mem[3010][3010][2];
int k;

int recur(int idx,int left,int req) {
	if (idx<left) return 2e9;
	//printf("%d %d %d\n",idx,left,req);
	if (mem[idx][left][req]!=-1) return mem[idx][left][req];
	if (idx<k) {
		return mem[idx][left][0]=mem[idx][left][1]=min(minn[idx-1]+tbl[idx],recur(idx-1,left,1));
	}
	if (req==1) {
		//if (idx-k+1<0) return mem[idx][left][req]=min(tbl[idx],recur(idx-1,left,1));
		return mem[idx][left][req]=min(recur(idx-1,idx-k+1,0)+tbl[idx],recur(idx-1,left,1));	
	} else {
		return mem[idx][left][req]=min(recur(idx-1,max(left-1,0),1)+tbl[idx],recur(idx-1,left,0));
	}
}

int main () {
	int n;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	minn[0]=tbl[0];
	for (int i=1;i<n;i++) {
		minn[i]=min(minn[i-1],tbl[i]);
	}
	memset(mem,-1,sizeof(mem));
	printf("%d\n",recur(n-1,n-k+1,0));
	//for (int i=0;i<n;i++) {
		//for (int j=0;j<n;j++) {
			//printf("%d,%d\t",mem[i][j][0],mem[i][j][1]);
		//}
		//printf("\n");
	//}
	return 0;
}

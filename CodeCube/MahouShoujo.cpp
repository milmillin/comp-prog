#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

map<pair<int,int> ,int> mem;

typedef struct {
	int val,idx;
} block;

bool operator< (const block &a, const block &b) {
	return a.val<b.val;
}

block tbl[20][100100];

int logg[100100];
int poww[20];

void init() {
	poww[0]=1;
	for (int i=1;i<20;i++) {
		poww[i]=poww[i-1]*2;
	}
	int cur=2;
	for (int i=1;i<100100;i++) {
		logg[i]=logg[i-1];
		if (i==cur) {
			logg[i]++;
			cur*=2;
		}
	}
}

const block& getMax(int lB,int rB) {
	int len = rB-lB+1;
	int lev = logg[len];
	int rr = rB-poww[lev]+1;
	return max(tbl[lev][lB],tbl[lev][rr]);
}

int n,k;

int getAns(int left,int right) {
	//printf("%d %d\n",left,right);
	if (left>right) return 0;
	if (mem.count(make_pair(left,right))) return mem[make_pair(left,right)];
	int base = getMax(left,right).val;
	int idx = getMax(left,right).idx;
	if (right-left+1<=k) return mem[make_pair(left,right)]=base;
	int now;
	int minn=2e9;
	for (int i=idx-k;i<idx;i++) {
		//if (i>=left) now+=getAns(left,i);
		//if (i+k+1<=right) now+=getAns(i+k+1,right);
		if (i<left-1||i+k>right) continue;
		now = getAns(left,i)+getAns(i+k+1,right);
		minn=min(minn,now);
	}
	if (minn==2e9) minn=0;
	//printf("%d\n",minn+base);
	return mem[make_pair(left,right)]=minn+base;
}

int main () {
	init();
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[0][i].val);
		tbl[0][i].idx=i;
	}
	for (int i=1;i<=logg[n];i++) {
		for (int j=0;j<=n-poww[i];j++) {
			tbl[i][j]=max(tbl[i-1][j],tbl[i-1][j+poww[i-1]]);
			//printf("%d ",tbl[i][j].val);
		}
		//printf("\n");
	}
	printf("%d\n",getAns(0,n-1));
	return 0;
}

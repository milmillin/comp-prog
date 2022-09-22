#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[200100];

typedef struct {
	int l,r,idx;
} query;

query q[200100];
int blkSz;
long long ans;
int cnt[1000100];
long long anss[200100];

bool operator< (const query &a, const query &b) {
	if (a.l/blkSz==b.l/blkSz) return a.r<b.r;
	return a.l/blkSz<b.l/blkSz;
}

bool cmp (const query &a, const query &b) {
	return a.idx<b.idx;
}

void add(int idx) {
	//printf("add %d %d %d\n",idx,tbl[idx],cnt[tbl[idx]]);
	//ans-=(long long)cnt[tbl[idx]]*cnt[tbl[idx]]*tbl[idx];
	ans+=(cnt[tbl[idx]]*2+1)*tbl[idx];
	cnt[tbl[idx]]++;
	//ans+=(long long)cnt[tbl[idx]]*cnt[tbl[idx]]*tbl[idx];
}

void rem(int idx) {
	//printf("rem %d %d\n",idx,tbl[idx]);
	//ans-=(long long)cnt[tbl[idx]]*cnt[tbl[idx]]*tbl[idx];
	ans-=(cnt[tbl[idx]]*2-1)*tbl[idx];
	cnt[tbl[idx]]--;
	//ans+=(long long)cnt[tbl[idx]]*cnt[tbl[idx]]*tbl[idx];
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	blkSz=(int)sqrt(n);
	for (int i=0;i<m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].l--;
		q[i].r--;
		q[i].idx=i;
	}
	sort(q,q+m);
	int curL,curR,newR,newL;
	curL=curR=0;
	ans=0;
	add(0);
	for (int i=0;i<m;i++) {
		newL=q[i].l;
		newR=q[i].r;
		//printf("%d %d\n",newL,newR);
		while (curL<newL) {
			rem(curL);
			curL++;
		}
		while (curL>newL) {
			curL--;
			add(curL);
		}
		while (curR<newR) {
			curR++;
			add(curR);
		}
		while (curR>newR) {
			rem(curR);
			curR--;
		}
		anss[q[i].idx]=ans;
	}
	for (int i=0;i<m;i++) {
		printf("%I64d\n",anss[i]);
	}
	return 0;
}

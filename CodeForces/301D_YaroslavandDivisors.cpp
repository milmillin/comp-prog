#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int tbl[200100];
int pos[200100];
long long bit[200100];

long long get(int idx) {
	long long sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void update(int idx,int val) {
	//printf("--update %d %d\n",idx,tbl[idx]);
	while (idx<200100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

typedef struct {
	int l,r;
	long long ans;
	int idx;
} query;

int blockSize;

bool operator< (const query &a, const query &b) {
	//printf("%d %d\n",a.l,b.l);
	//if ((a.l-1)/blockSize!=(b.l-1)/blockSize) return (a.l-1)/blockSize<(b.l-1)/blockSize;
	return a.r<b.r;
}

bool cmp (const query &a, const query &b) {
	return a.idx<b.idx;
}

int n;

void add(int idx) {
	/*
	if (idx==0) return;
	int cur=tbl[idx];
	//printf("add %d\n",tbl[idx]);
	while (cur<=n) {
		update(pos[cur],1);
		cur+=tbl[idx];
	}
	*/
	for (int i=1;i*i<=tbl[idx];i++) {
		if (tbl[idx]%i) continue;
		if (pos[i]<=idx) update(pos[i],1);
		if (i*i!=tbl[idx]&&pos[tbl[idx]/i]<=idx) update(pos[tbl[idx]/i],1);
	}
	for (int i=2;tbl[idx]*i<=n;i++) {
		if (pos[tbl[idx]*i]>idx) continue;
		update(pos[tbl[idx]*i],1);
	}
}

void remove(int idx) {
	if (idx==0) return;
	int cur=tbl[idx];
	//printf("rem %d\n",tbl[idx]);
	while (cur<=n) {
		//printf("--%d\n",pos[cur]);
		update(pos[cur],-1);
		cur+=tbl[idx];
	}
}

int main () {
	int m;
	scanf("%d%d",&n,&m);
	int x;
	blockSize = (int)sqrt(n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		pos[tbl[i]]=i;
	}
	int a,b;
	vector<query> qq(m);
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		qq[i]=query{a,b,0,i};
	}

	sort(qq.begin(),qq.end());

	int curL=0,curR=0;


	int newL,newR;
	for (int i=0;i<m;i++) {
		newL=qq[i].l;
		newR=qq[i].r;
		//printf("%d %d %d\n",i,newL,newR);
		/*
		while (curL>newL) {
			curL--;
			add(curL);
		}
		while (curL<newL) {
			remove(curL);
			curL++;
		}
		*/
		while (curR<newR) {
			curR++;
			add(curR);
		}
		/*
		while (curR>newR) {
			remove(curR);
			curR--;
		}
		*/
		qq[i].ans=get(newR)-get(newL-1);
		//printf("ans %d %d\n",get(newR),get(newL-1));
	}
	sort(qq.begin(),qq.end(),cmp);
	for (int i=0;i<m;i++) {
		printf("%I64d\n",qq[i].ans);
	}
	return 0;
}

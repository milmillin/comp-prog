#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct qq {
	int l,r;
	int id;
};

int box;
int ans[300100];

bool operator< (const qq &a, const qq &b) {
	if (a.l/box!=b.l/box) return a.l<b.l;
	return a.r<b.r;
}

//bool cmp (const qq &a, const qq &b) {
	//return a.id<b.id;
//}

int tbl[300100];
int cnt[50100];
int unq;

void add(int idx) {
	//printf("add %d\n",idx);
	if (0==cnt[tbl[idx]]++) unq++;
}

void rem(int idx) {
	//printf("rem %d\n",idx);
	if (0==--cnt[tbl[idx]]) unq--;
}

qq que[300100];

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	box=(int)sqrt(n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	int a,b;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		que[i]=qq{a,b,i};
	}
	sort(que,que+q);
	int l=1;
	int r=0;
	unq=0;
	for (int i=0;i<q;i++) {
		//printf("%d %d\n",que[i].l,que[i].r);
		while (l<que[i].l) if (0==--cnt[tbl[l++]]) unq--;
		while (l>que[i].l) if (0==cnt[tbl[--l]]++) unq++;
		while (r>que[i].r) if (0==--cnt[tbl[r--]]) unq--;
		while (r<que[i].r) if (0==cnt[tbl[++r]]++) unq++;
		ans[que[i].id]=unq;
	}
	for (int i=0;i<q;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

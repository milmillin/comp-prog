#include <cstdio>
#include <algorithm>

using namespace std;

//int tbl[100100];
//int par[100100];

struct ei{
	int idx;
	int par;
};

bool cmp(const ei &a, const ei &b) {
	return a.idx<b.idx;
}

ei tbl[100100];

int findpar(int idx) {
	if (tbl[idx].par==idx) return idx;
	return tbl[idx].par=findpar(tbl[idx].par);
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i].idx);
		tbl[i].par=i;
	}
	int a,b;
	for (int i=0;i<n-2;i++) {
		scanf("%d%d",&a,&b);
		tbl[findpar(a)].par=findpar(b);
	}
	for (int i=1;i<=n;i++) findpar(i);
	sort(tbl+1,tbl+n+1,cmp);

	int mn=2e9;
	for (int i=1;i<n;i++) {
		//printf("%d ",par[i]);
		if (tbl[i].par!=tbl[i+1].par) {
			mn=min(mn,abs(tbl[i].idx-tbl[i+1].idx));
		}
	}
	printf("%d\n",mn);
	return 0;
}

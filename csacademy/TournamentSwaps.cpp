#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int tbl[200100];

struct ei {
	int a,b;
};

ei comb(const ei &a, const ei &b) {
	vector<int> tmp;
	tmp.push_back(a.a);
	tmp.push_back(a.b);
	tmp.push_back(b.a);
	tmp.push_back(b.b);
	sort(tmp.begin(),tmp.end());
	return ei{tmp[3],tmp[2]};
}

ei tree[400100];
int mn[20];
void build(int idx,int l,int r,int dep) {
	if (l+2==r) {
		tree[idx]=ei{max(tbl[l],tbl[l+1]),min(tbl[l],tbl[l+1])};
		mn[dep]=min(mn[dep],tree[idx].b);
		return;
	}
	int m=(l+r)>>1;
	build(idx*2+1,l,m,dep+1);
	build(idx*2+2,m,r,dep+1);
	tree[idx]=comb(tree[idx*2+1],tree[idx*2+2]);
	mn[dep]=min(mn[dep],tree[idx].b);
	return;
}

int ans[200100];
void f() {
	int n;
	scanf("%d",&n);
	int nn=1<<n;
	for (int i=0;i<nn;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(mn,63,sizeof(mn));
	build(0,0,nn,0);
	memset(ans,0,sizeof(ans));
	for (int i=0;i<20;i++) {
		if (mn[i]>200100) continue;
		ans[mn[i]]=1;
	}
	for (int i=0;i<nn;i++) {
		if (i) ans[i]+=ans[i-1];
		printf("%d ",ans[i]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

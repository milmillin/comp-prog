#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct st {
	int a,b;
};

bool cmp(const st &a, const st &b) {
	if (a.a==b.a) return a.b<b.b;
	return a.a>b.a;
}

void f() {
	int n;
	scanf("%d",&n);
	vector<st> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].a,&tbl[i].b);
	}
	sort(tbl.begin(),tbl.end(),cmp);
	/*	
	for (int i=0;i<n;i++) {
		printf("%d ",tbl[i].b);
	}
	printf("\n---\n");
	*/
	vector<int> stk(n,2e9);
	vector<int>::iterator it;
	int ans=0;	
	for (int i=0;i<n;i++) {
		it=upper_bound(stk.begin(),stk.end(),tbl[i].b);
		*it=tbl[i].b;
		ans=max(ans,it-stk.begin()+1);
	}
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}

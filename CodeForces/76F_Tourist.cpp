#include <cstdio>
#include <algorithm>

using namespace std;

struct event {
	int a,b;
};

bool cmp (const event &a, const event &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

event tbl[100100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].a,&tbl[i].b);
	}
	int v,a,b;
	scanf("%d",&v);
	for (int i=0;i<n;i++) {
		a=v*tbl[i].b-tbl[i].a;
		b=v*tbl[i].b+tbl[i].a;
		tbl[i]=event{a,b};
	}
	sort(tbl,tbl+n,cmp);
	//for (int i=0;i<n;i++) {
		//printf("%d %d\n",tbl[i].a,tbl[i].b);
	//}
	vector<int> stk(n+1,2e9);
	vector<int> stk1(n+1,2e9);
	stk1[0]=0;
	int ans=0;
	int ans1=0;
	vector<int>::iterator it,it2;
	for (int i=0;i<n;i++) {
		it = upper_bound(stk.begin(),stk.end(),tbl[i].b);
		*it=tbl[i].b;
		ans=max(ans,it-stk.begin()+1);
		if (tbl[i].a>=0) {
			it2 = upper_bound(stk1.begin(),stk1.end(),tbl[i].b);
			if (it2!=stk1.begin()) *it2=tbl[i].b;
			ans1=max(ans1,it2-stk1.begin());
		}
	}
	printf("%d %d\n",ans1,ans);
	return 0;
}

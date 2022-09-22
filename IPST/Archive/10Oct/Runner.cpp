#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
	int idx,velo,time;
} run;

bool operator< (const run &a, const run &b) {
	if (a.time==b.time) {
		return a.velo>b.velo;
	}
	return a.time<b.time;
}

void f() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<run>tbl(n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		tbl[i].idx=i;
		tbl[i].velo=a;
		tbl[i].time=m*1000/a+b;
	}
	sort(tbl.begin(),tbl.end());
	for (int i=0;i<n;i++) {
		printf("%d\n",tbl[i].idx+1);
	}
	return;
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}

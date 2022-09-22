#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	sort(tbl.begin(),tbl.end());
	int cnt=0;
	int r=n-1;
	int l=0;
	while (r>=l) {
		l+=(int)ceil(50.0/tbl[r])-1;
		if (r<l) break;
		cnt++;
		r--;
		//printf("%d\n",l);
	}
	printf("%d\n",cnt);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}

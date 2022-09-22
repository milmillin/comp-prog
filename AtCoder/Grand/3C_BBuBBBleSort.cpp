#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct ei {
	int val,idx;
};

bool operator< (const ei &a, const ei &b) {
	return a.val<b.val;
}

int main () {
	int n;
	scanf("%d",&n);
	int cnt=0;
	vector<ei> tbl(n);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		tbl[i].val=x;
		tbl[i].idx=i+1;
	}
	sort(tbl.begin(),tbl.end());
	for (int i=0;i<n;i++) {
		tbl[i].val=i+1;
		if (i%2&&tbl[i].idx%2!=(i+1)%2) cnt++;
	}
	printf("%d\n",cnt);	
	return 0;
}

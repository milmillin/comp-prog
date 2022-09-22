#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

struct p {
	int val,wid;
};

int cnt[200100];

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	tbl.push_back(0);
	vector<p> stk;
	stk.push_back(p{0,1});
	int cur;
	for (int i=0;i<=n;i++) {
		//printf("%d\n",tbl[i]);
		cur=0;
		while (!stk.empty()&&stk.back().val>tbl[i]) {
			cur+=stk.back().wid;
			cnt[cur]=max(cnt[cur],stk.back().val);
			stk.pop_back();
		}
		cur++;
		stk.push_back(p{tbl[i],cur});
	}
	cur=0;
	for (int i=n;i>=1;i--) {
		if (cnt[i]>cur) cur=cnt[i];
		cnt[i]=cur;
	}
	for (int i=1;i<=n;i++) {
		printf("%d ",cnt[i]);
	}
	printf("\n");
	return 0;
}

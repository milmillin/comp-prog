#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100010];
int rgt[100010];
int lft[100010];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	tbl[0]=0;
	tbl[n+1]=0;
	vector<int> stk;
	long long maxx=0;
	int cur;
	for (int i=1;i<=n+1;i++) {
		//cur=1;
		while (!stk.empty()&&tbl[stk.back()]>tbl[i]) {
			rgt[stk.back()]=(i-stk.back());
			stk.pop_back();
		}
		stk.push_back(i);
	}

	stk.clear();
	for (int i=n;i>=0;i--) {
		//cur=1;
		while (!stk.empty()&&tbl[stk.back()]>tbl[i]) {
			lft[stk.back()]=(stk.back()-i);
			//maxx=max(maxx,((long long)tbl[i])*(lft[i]+rgt[i]-1));
			stk.pop_back();
		}
		stk.push_back(i);
	}

	for (int i=1;i<=n;i++) {
		maxx=max(maxx,(long long)tbl[i]*(lft[i]+rgt[i]-1));
		//printf("%d %d %d\n",lft[i],rgt[i],tbl[i]*(lft[i]+rgt[i]-1));
	}

	printf("%lld\n",maxx);
	return 0;
}

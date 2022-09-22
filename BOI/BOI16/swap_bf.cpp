#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>

using namespace std;


int tbl[30];
vector<vector<int>> candid;
int n;

void solve(int i) {
	if (i==n+1) {
		vector<int> tmp;
		for (int i=1;i<=n;i++) {
			tmp.push_back(tbl[i]);
		}
		candid.push_back(tmp);
		return;
	}
	solve(i+1);
	swap(tbl[i/2],tbl[i]);
	solve(i+1);
	swap(tbl[i/2],tbl[i]);
}


int main () {
	scanf("%d",&n);
	assert(n<=20);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	solve(2);
	sort(candid.begin(),candid.end());
	for (auto i:candid.front()) {
		printf("%d ",i);
	}
	printf("\n");
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int tbl[100100];
bool mark[100100];
int n;

int solve() {
	vector<int> pos;
	for (int i=1;i<=n;i++) {
		if (mark[i]) pos.push_back(tbl[i]);
	}
	assert(pos.size()%2==1);
	//for (auto i:pos) {
		//printf("%d ",i);
	//}
	//printf("\n");
	vector<int> left;
	left.push_back(0);
	for (int i=1;i<(int)pos.size();i+=2) {
		left.push_back(pos[i]-pos[i-1]+left.back());
	}
	vector<int> right;
	right.push_back(0);
	for (int i=pos.size()-2;i>=0;i-=2) {
		right.push_back(pos[i+1]-pos[i]+right.back());
	}
	assert(right.size()==left.size());
	int mn=1e9;
	for (int i=0;i<(int)left.size();i++) {
		mn=min(mn,left[i]+right[right.size()-i-1]);
	}
	return mn;
}

int main () {
	scanf("%d",&n);
	assert(n<50000);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}	
	int x;
	scanf("%d",&x);
	mark[x]=true;
	int a,b;
	for (int i=0;i<n/2;i++) {
		scanf("%d%d",&a,&b);
		mark[a]=true;
		mark[b]=true;
		printf("%d\n",solve());
	}
	return 0;
}

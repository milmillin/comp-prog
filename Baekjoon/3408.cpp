#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int tbl[200100];
vector<int> pos[200100];
int nxt[200100];
int prv[200100];

bool solve(int l,int r) {
	int sz=r-l;
	if (sz<=1) return true;
	int mid;
	for (int i=0;i<sz;i++) {
		if (i%2) {
			mid=r-i/2-1;
		} else {
			mid=l+i/2;
		}
		if (nxt[mid]>=r&&prv[mid]<l) {
			return solve(l,mid)&&solve(mid+1,r);
		}	
	}
	return false;
}

void f() {
	int n;
	scanf("%d",&n);
	map<int,int> comp;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		comp[tbl[i]];	
	}
	int cnt=0;
	for (auto &i:comp) {
		i.second=cnt++;
	}
	for (int i=0;i<n;i++) {
		tbl[i]=comp[tbl[i]];
		pos[tbl[i]].push_back(i);
	}
	for (int i=0;i<n;i++) {
		auto x=lower_bound(pos[tbl[i]].begin(),pos[tbl[i]].end(),i);
		if (x==pos[tbl[i]].begin()) {
			prv[i]=-1;
		} else {
			prv[i]=*(x-1);
		}
		x++;
		if (x==pos[tbl[i]].end()) {
			nxt[i]=n;
		} else {
			nxt[i]=*x;
		}
		//printf("%d %d\n",prv[i],nxt[i]);
	}	
	printf("%s\n",solve(0,n)?"non-boring":"boring");
	for (int i=0;i<n;i++) {
		pos[tbl[i]].clear();
	}
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

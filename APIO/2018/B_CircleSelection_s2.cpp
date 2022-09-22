#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct circle {
	int x,y,r;
	int id;
};

bool operator< (const circle &a, const circle &b) {
	if (a.r!=b.r) return a.r>b.r;
	return a.id<b.id;
}

bool intersect (const circle &a, const circle &b) {
	long long tmp=(long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y);
	//printf("aa %d %d %lld\n",a.id,b.id,tmp);
	return tmp<=(long long)(a.r+b.r)*(a.r+b.r);
}

struct ei {
	int pos;
	int id;
	int another;
};

bool operator< (const ei &a, const ei &b) {
	if (a.pos!=b.pos) return a.pos<b.pos;
	if (a.id!=b.id) return a.id<b.id;
	return a.another<b.another;
}

vector<circle> tbl;
int ans[300100];

set<ei> aa;

int main () {
	int n;
	scanf("%d",&n);
	int a,b,c;
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		assert(b==0);
		aa.insert(ei{a-c,i,a+c});
		aa.insert(ei{a+c,i,a-c});
		tbl.push_back(circle{a,b,c,i});
	}
	sort(tbl.begin(),tbl.end());
	for (auto &i:tbl) {
		if (ans[i.id]) continue;
		ans[i.id]=i.id;
		aa.erase(ei{i.x-i.r,i.id,i.x+i.r});
		aa.erase(ei{i.x+i.r,i.id,i.x-i.r});
		auto lo=aa.lower_bound(ei{i.x-i.r,-100,(int)-1e9-1});
		auto hi=aa.upper_bound(ei{i.x+i.r,(int)1e9,(int)1e9+1});
		for (auto it=lo;it!=hi;it++) {
			if (ans[it->id]) continue;
			ans[it->id]=i.id;
		}
		aa.erase(lo,hi);
	}
	for (int i=1;i<=n;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}

#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int tbl[500100];
int blk;

struct cluster {
	int tag;
	vector<int> raw;
	set<int> mp[500000];	
	
	int query() {
		auto& vec = mp[tag];			
		if (vec.empty()) return -1;
		return *vec.rbegin();
	}

	void insert(int val) {
		raw.push_back(val);
		auto& vec = mp[raw.back()];
		vec.insert(raw.size()-1);
	}

	void inc(int pos) {
		auto& vec = mp[raw[pos]];
		vec.erase(pos);
		raw[pos]--;
		auto& vec2 = mp[raw[pos]];
		vec2.insert(pos);
	}
};

cluster cl[800];

int ans[500100];

int blkcnt;

void add(int pos) {
	int spos=pos/blk;
	if (pos%blk) {
		for (int i=pos;i%blk!=0;i++) {
			//printf("add %d %d\n",spos,i%blk);
			cl[spos].inc(i%blk);
		}
		spos++;
	}
	for (int i=spos;i<blkcnt;i++) {
		//printf("add tag %d\n",i);
		cl[i].tag++;
	}
}

int main () {
	int n;
	scanf("%d",&n);
	blk=(int)floor(sqrt(n));
	blkcnt=(n-1)/blk+1;
	//printf("blk %d\n",blk);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		tbl[i]-=i;
		cl[i/blk].insert(tbl[i]);	
	}

	for (int i=0;i<n;i++) {
		//printf("%d\n",i);
		int cur=-1;
		for (int j=0;j<blkcnt;j++) {
			int tmp=cl[j].query();	
			//printf("%d ",tmp);
			if (tmp!=-1) cur=tmp+j*blk;
		}	
		//printf("\n");
		//printf("--%d\n",cur);
		assert(cur!=-1);
		//if (cur==-1) {
			//printf("fuck\n");
			//return 3;
		//}
		ans[cur]=i+1;
		add(cur);	
	}

	for (int i=0;i<n;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");

	return 0;
}

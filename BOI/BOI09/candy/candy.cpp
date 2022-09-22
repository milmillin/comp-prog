#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct candy {
	int s,t;
	int cur;
	int id;
};

bool operator< (const candy &a,const candy &b) {
	if (a.s!=b.s) return a.s>b.s;
	return a.t<b.t;
}

bool cmp(const candy &a,const candy &b) {
	if (a.t!=b.t) return a.t<b.t;
	return a.s<b.s;
}

vector<candy> tbl;
bool cmp2(const int x, const int y) {
	candy &a=tbl[x];
	candy &b=tbl[y];
	if (a.s+a.t!=b.s+b.t) return a.s+a.t<b.s+b.t;
	return a.s>b.s;
}


vector<int> pth[100100];
int indeg[100100];

priority_queue<candy> q;

int main () {
	int n;
	scanf("%d",&n);
	assert(n<10000);
	int s,t;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&s,&t);
		tbl.push_back(candy{s,t,0});
	}
	sort(tbl.begin(),tbl.end(),cmp);
	for (int i=0;i<n;i++) {
		tbl[i].id=i;
		for (int j=i+1;j<n;j++) {
			if (abs(tbl[j].s-tbl[i].s)<=tbl[j].t-tbl[i].t) {
				pth[i].push_back(j);
				indeg[j]++;
			}
		}
		if (indeg[i]==0) {
			q.push(tbl[i]);
		}
		sort(pth[i].begin(),pth[i].end(),cmp2);
	}
	int cur=1;
	while(!q.empty()) {
		auto now = q.top();
		q.pop();
		if (tbl[now.id].cur==0) {
			tbl[now.id].cur=cur++;
		}
		for (auto i:pth[now.id]) {
			if (tbl[i].cur!=0) continue;
			tbl[i].cur=tbl[now.id].cur;
			q.push(tbl[i]);
			break;
		}
		for (auto i:pth[now.id]) {
			if (tbl[i].cur!=0) continue;
			indeg[i]--;
			if (!indeg[i]) q.push(tbl[i]);
		}
	}
	printf("%d\n",cur-1);
	for (int i=0;i<n;i++) {
		assert(tbl[i].cur!=0);
		printf("%d %d %d\n",tbl[i].s,tbl[i].t,tbl[i].cur);
	}
	return 0;
}

#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int a[100100];
int b[100100];
int c[100100];
int d[100100];
int x[100100];
int y[100100];
int k[100100];

const int size = (1<<18);

struct node {
	int ord,idx;
};

struct tree {
	vector<node> nodes[size*2];
	
	void add(int idx,int l,int r,int ll,int rr, node nd) {
		if (rr<=l||ll>=r) return;
		if (ll<=l&&rr>=r) {
			nodes[idx].push_back(nd);
			return;
		}
		int m = (l+r)>>1;
		add(idx*2,l,m,ll,rr,nd);
		add(idx*2+1,m,r,ll,rr,nd);
	}	

	void rem(int idx,int l,int r,int ll,int rr) {
		if (rr<=l||ll>=r) return;
		if (ll<=l&&rr>=r) {
			nodes[idx].pop_back();
			return;
		}
		int m = (l+r)>>1;
		rem(idx*2,l,m,ll,rr);
		rem(idx*2+1,m,r,ll,rr);
	}
	
	int get(int pos) {
		pos+=size;

		int last=-1;
		int ret=-1;

		while (pos) {
			if (!nodes[pos].empty()&&nodes[pos].back().ord>last) {
				last=nodes[pos].back().ord;
				ret = nodes[pos].back().idx;
			}
			pos/=2;
		}
		return ret;
	}
} T;

struct event {
	int x;
	int p;
	int y1;
	int y2;
};

bool operator< (const event &a, const event &b) {
	if (a.x!=b.x) return a.x<b.x;
	if (a.p!=b.p) return a.p<b.p;
	if (a.y1!=b.y1) return a.y1<b.y1;
	return a.y2<b.y2;
}

set<int> cols[100100];
vector<int> pth[100100];
int indeg[100100];
int loc[100100];
int ans[100100];

void merge(int a,int b) {
	if (cols[loc[a]].size()<cols[loc[b]].size()) swap(loc[a],loc[b]);
	for (auto &i:cols[loc[b]]) {
		cols[loc[a]].insert(i);	
	}	
}

void dfs(int idx) {
	for (auto i:pth[idx]) {
		dfs(i);
		merge(idx,i);
	}
	ans[idx]=cols[loc[idx]].size();
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int> cmp;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		cmp.push_back(b[i]);
		cmp.push_back(d[i]);
	}
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&x[i],&y[i],&k[i]);
		cmp.push_back(y[i]);
	}
	sort(cmp.begin(),cmp.end());
	cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
	for (int i=0;i<n;i++) {
		b[i]=lower_bound(cmp.begin(),cmp.end(),b[i])-cmp.begin();
		d[i]=lower_bound(cmp.begin(),cmp.end(),d[i])-cmp.begin();
	}
	for (int i=0;i<m;i++) {
		y[i]=lower_bound(cmp.begin(),cmp.end(),y[i])-cmp.begin();
	}

	vector<event> events;

	for (int i=0;i<n;i++) {
		events.push_back(event{a[i],i+1,b[i],d[i]});
		events.push_back(event{c[i]+1,-i-1,b[i],d[i]});
	}
	for (int i=0;i<m;i++) {
		events.push_back(event{x[i],100100,y[i],k[i]});
	}
	sort(events.begin(),events.end());
	
	int cnt=0;
	for (auto &e:events) {
		cnt++;
		//printf("-- %d %d %d %d\n",e.x,e.p,e.y1,e.y2);
		if (e.p==100100) {
			int idx = T.get(e.y1);
			//printf("---  %d\n",idx);
			if (idx!=-1) cols[idx].insert(e.y2);
		} else if (e.p>0) {
			int idx = T.get(e.y1);
			if (idx!=-1) {
				pth[idx].push_back(e.p);
				indeg[e.p]++;
			}
			T.add(1,0,size,e.y1,e.y2+1,node{cnt,e.p});
		} else {
			T.rem(1,0,size,e.y1,e.y2+1);
		}
	}

	for (int i=1;i<=n;i++) {
		loc[i]=i;
	}

	for (int i=1;i<=n;i++) {
		if (indeg[i]==0) dfs(i);
	}
	for (int i=1;i<=n;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

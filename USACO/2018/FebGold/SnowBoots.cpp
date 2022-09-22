#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
	int x,val;
};

bool operator< (const point &a, const point &b) {
	if (a.val!=b.val) return a.val<b.val;
	return a.x<b.x;
}

vector<point> tbl;

struct node {
	int idx;
	int val;
};

node seg[300100];
int pos[300100];

void build(int idx,int l,int r) {
	if (l+1==r) {
		seg[idx].idx=-1;
		seg[idx].val=0;
		pos[l]=idx;
		return;
	}
	int m = (l+r)>>1;
	build(idx*2,l,m);
	build(idx*2+1,m,r);
}

int getId(int idx,int l,int r,int k) {
	if (k<l) return -1;
	if (r<=k+1) return seg[idx].idx;
	int m = (l+r)>>1;
	return max(getId(idx*2,l,m,k),getId(idx*2+1,m,r,k));	
}

void update(int idx,int l,int r,int k,int val) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		seg[idx].idx=l;
		seg[idx].val=val;
		return;
	}
	int m = (l+r)>>1;
	update(idx*2,l,m,k,val);
	update(idx*2+1,m,r,k,val);
	seg[idx].idx=max(seg[idx*2].idx,seg[idx*2+1].idx);
	seg[idx].val=max(seg[idx*2].val,seg[idx*2+1].val);
}

map<int,int> minDis;

int main () {
	freopen("snowboots.in","r",stdin);
	freopen("snowboots.out","w",stdout);
	int n,b;
	scanf("%d%d",&n,&b);
	int x;
	vector<int> hgt;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		tbl.push_back(point{i,x});
		hgt.push_back(x);
	}
	sort(hgt.begin(),hgt.end());
	sort(tbl.begin(),tbl.end());
	hgt.erase(unique(hgt.begin(),hgt.end()),hgt.end());
	build(1,0,n);
	int tmp;
	int rgt;
	for (auto &i:tbl) {
		tmp = getId(1,0,n,i.x);
		if (tmp==-1) {
			update(1,0,n,i.x,n-i.x);
			continue;
		}
		rgt = seg[pos[tmp]].val+tmp;
		update(1,0,n,tmp,i.x-tmp);
		update(1,0,n,i.x,rgt-i.x);
		minDis[i.val]=seg[1].val;
	}
	int a,c;
	for (int i=0;i<b;i++) {
		scanf("%d%d",&a,&c);
		auto it = upper_bound(hgt.begin(),hgt.end(),a);
		it--;
		printf("%d\n",(minDis[*it]<=c)?1:0);	
	}
	return 0;
}

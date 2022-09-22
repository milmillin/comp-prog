#include <bits/stdc++.h>
//#include "grader.cpp"
#include "prize.h"

using namespace std;

pair<int,int> ans[200100];
bool asked[200100];
set<int> contains[200100];

struct range {
	int l,r;
	int size() {
		return r-l+1;
	}
};

struct event {
	int idx;
	bool isOpen;
};

queue<range> tbl;
bitset<200100> work;

pair<int,int> aa(int i) {
	if (asked[i]) return ans[i];
	//printf("asked %d\n",i);
	asked[i]=true;
	vector<int> a = ask(i);
	return ans[i]={a[0],a[1]}; 
}

typedef set<int>::iterator sit;

int find_best(int n) {
	tbl.push(range{0,n});
	int boundl=0;
	int boundr=n;
	work.set();
	while (!tbl.empty()) {
		range cur=tbl.front();
		tbl.pop();
		//printf("--%d %d %d %d\n",cur.l,cur.r,boundl,boundr);
		int l=max(boundl,cur.l);
		int r=min(boundr,cur.r);
		int sq=sqrt(r-l);
		if (l+1==r) {
			auto rr=aa(l);
			if (rr.first==0&&rr.second==0) return l;
			work[l]=false;
			if (rr.first==0) boundl=l+1;
			if (rr.second==0) boundr=l;
			l=max(boundl,l);
			r=min(boundr,r);
		}
		for (int i=sq;i<r;i+=sq) {
			if (i<boundl) continue;
			if (i>=boundr) continue;
			auto rr=aa(i);
			if (rr.first==0&&rr.second==0) return i;
			work[i]=false;
			if (rr.first==0) boundl=i+1;
			if (rr.second==0) boundr=i;
			l=max(boundl,l);
			r=min(boundr,r);
			set<int> &same_type = contains[rr.first+rr.second];
			for (sit it=same_type.begin();it!=same_type.end();it++) {
				if (aa(*it).first==rr.first) {
					//printf("rem %d %d\n",*it,i);
					for (int j=*it;j<i;j++) {
						work[j]=false;
					}
					break;
				}
			}
			same_type.insert(i);
		}
		int curl=-1;
		for (int i=l;i<r;i++) {
			if (work[i]) {
				if (curl==-1) curl=i;
			} else {
				if (curl!=-1) tbl.push(range{curl,i}),curl=-1;
			}
		}
	}
}

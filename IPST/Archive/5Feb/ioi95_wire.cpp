#include <cstdio>
#include <vector>
#include "wirelib.h"

using namespace std;

int ans[1000];
bool lamp[1000];

void recur(int st,int end, vector<int> aL) {
	if (aL.empty()) return;
	if (end==st) return;
	if (end-st==1) {
		for (int i=0;i<aL.size();i++) {
			ans[aL[i]]=st;
		}
		return;
	}
	vector<int> aL1;
	vector<int> aL2;
	int mid = (st+end)/2;
	for (int i=st;i<mid;i++) {
		if (!lamp[i]) {
			lamp[i]=true;
			cmd_C(i);
		}
	}
	for (int i=mid;i<end;i++) {
		if (lamp[i]) {
			lamp[i]=false;
			cmd_C(i);
		}
	}
	for (int i=0;i<aL.size();i++) {
		if (cmd_T(aL[i])) {
			aL1.push_back(aL[i]);
		} else {
			aL2.push_back(aL[i]);
		}
	}
	recur(st,mid,aL1);
	recur(mid,end,aL2);
}

int main () {
	int m;
	m=wire_init();
	vector<int> tmp(m);
	for (int i=0;i<m;i++) {
		tmp[i]=i+1;
	}
	recur(1,m+1,tmp);
	cmd_D(ans);
	return 0;
}

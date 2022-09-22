#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct ee {
	int wid,dep;
};

bool operator< (const ee &a, const ee &b) {
	return a.wid<b.wid;
}


int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	
	vector<int> tbl(n+1);

	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	tbl[n]=0;
	reverse(tbl.begin(),tbl.end());
	vector<ee> stk;
	for (int i=0;i<n;i++) {
		while (!stk.empty()&&stk.back().wid>tbl[i]) stk.pop_back();
		//if (!stk.empty()&&stk.back().wid==tbl[i]) continue;
		stk.push_back(ee{tbl[i],n-i+1});
	}
	//for (auto i:stk) {
		//printf("%d %d\n",i.dep,i.wid);
	//}
	auto cur=stk.begin();
	int pnt=n+1;
	int x;
	for (int i=0;i<q;i++) {
		scanf("%d",&x);
		auto res = lower_bound(cur,stk.end(),ee{x,0});
		res--;
		pnt = min(pnt-1,res->dep-1);
		while (cur!=stk.end()&&cur->dep>pnt) cur++;
	}
	printf("%d\n",max(0,pnt));
	return 0;
}

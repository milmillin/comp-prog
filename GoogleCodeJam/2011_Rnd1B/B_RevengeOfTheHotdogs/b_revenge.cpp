#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool work(double time,double d,vector<pair<int,int>> &tbl) {
	double left=-1e18;	
	for (auto &i:tbl) {
		double right=i.first+time;
		left=max(left,i.first-time);
		for (int j=0;j<i.second;j++) {
			if (left>right) return false;
			//printf("%f ",left);
			left+=d;	
		}
	}
	//printf("\n");
	return true;
}


double eps=1e-6;
void f() {
	int c,d;
	scanf("%d%d",&c,&d);
	int p,v;
	vector<pair<int,int>> tbl;
	tbl.reserve(c);
	for (int i=0;i<c;i++) {
		scanf("%d%d",&p,&v);
		tbl.push_back({p,v});
	}
	sort(tbl.begin(),tbl.end());
	double lo=0;
	double hi=1e18;
	double mid;
	for (int ii=0;ii<80;ii++) {
		mid=(lo+hi)/2;
		//printf("%f: ",mid);
		if (work(mid,d,tbl)) {
			hi=mid;
		} else {
			lo=mid;
		}
		//printf("\n");
	}	
	printf("%f\n",lo);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		cerr << i << endl;
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}

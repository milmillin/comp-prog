#include "traffic.h"
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;


struct trf{
	int a,b,c,d;
};

vector<trf> ans;

void solveV(int i,int l,int r,int sum) {
	if (l+1==r) {
		ans.push_back(trf{i,l,i,r});
		return;
	}
	int m=(l+r)>>1;
	int res = traffic_query(i,l,i,m);
	if (res>=m-l+1) {
		solveV(i,l,m,res);			
	}
	if (sum-res>=r-m+1) {
		solveV(i,m,r,sum-res);
	}
}

void solveH(int i,int l,int r,int sum) {
	if (l+1==r) {
		ans.push_back(trf{l,i,r,i});
		return;
	}
	int m=(l+r)>>1;
	int res = traffic_query(l,i,m,i);
	if (res>=m-l+1) {
		solveH(i,l,m,res);			
	}
	if (sum-res>=r-m+1) {
		solveH(i,m,r,sum-res);
	}
}


int main() {
	int n,k;
	traffic_init(&n,&k);
	//int res = traffic_query(1,1,5,2);
	//traffic_report(4,3,4,4,0,0,0,0);
	
	//test vertical
	for (int i=1;i<=n;i++) {
		if (ans.size()==k) break;
		int res=traffic_query(i,1,i,n);
		if (res>=n) {
			solveV(i,1,n,res);	
			//printf("yayv\n");
		}
	}	
	//for (auto &i:ans) {
		//printf("%d %d %d %d\n",i.a,i.b,i.c,i.d);
	//}
	//test horizontal
	for (int i=1;i<=n;i++) {
		if (ans.size()==k) break;
		int res=traffic_query(1,i,n,i);
		if (res>=n) {
			solveH(i,1,n,res);
			//printf("yayh\n");
		}	
	}
	//printf("---\n");
	//for (auto &i:ans) {
		//printf("%d %d %d %d\n",i.a,i.b,i.c,i.d);
	//}
	assert(k==ans.size());
	if (k==1) {
		traffic_report(ans[0].a,ans[0].b,ans[0].c,ans[0].d,0,0,0,0);
	} else {
		traffic_report(ans[0].a,ans[0].b,ans[0].c,ans[0].d,ans[1].a,ans[1].b,ans[1].c,ans[1].d);
	}
	return 0;
}

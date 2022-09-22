#include <cstdio>
#include <map>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[200100];

vector<int> pth[200100];


int min3(int x,vector<int> &y) {
	int ans=tbl[y[0]];
	for (int i=1;i<(int)y.size();i++) {
		ans=min(ans,tbl[y[i]]);
	}
	return min(x,ans);
}

int minvec(vector<int> &x) {
	int ans=1e9;
	for (int i=0;i<(int)x.size();i++) {
		ans=min(ans,tbl[x[i]]);
	}
	return ans;
}


map<int,int> dp[200100];

int minid(int id,int val) {
	if (dp[id].find(val)!=dp[id].end()) return dp[id][val];
	int x=minvec(pth[id]);
	if (val<x) return dp[id][val]=id;
	if (tbl[pth[id][0]]==x) return dp[id][val]=minid(pth[id][0],val);
	//val < tbl[pth[id][0]]
	if (val<tbl[pth[id][0]]) {
		return dp[id][val]=min(minid(pth[id][0],val),minid(pth[id][1],val));
	}
	//val > tbl[pth[id][0]]
	int k1=minid(pth[id][0],tbl[pth[id][0]]);
	int k2=minid(pth[id][1],tbl[pth[id][0]]);
	if (k1<k2) {
		return dp[id][val]=minid(pth[id][1],val);
	} else {
		return dp[id][val]=minid(pth[id][0],val);
	}
}


int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	for (int i=2;i<=n;i++) {
		pth[i/2].push_back(i);
	}
	int cur;

	int mn,mx;
	for (int i=1;i<=n/2;i++) {
		cur=min3(tbl[i],pth[i]);
		if (tbl[i]==cur) {
			//min x y
			continue;
		}
		if (tbl[pth[i][0]]==cur) {
			//x min y
			swap(tbl[i],tbl[pth[i][0]]);
			continue;
		}
		assert(pth[i].size()==2);

		if (tbl[i]>tbl[pth[i][0]]) {
			swap(tbl[i],tbl[pth[i][0]]);
		}
		//min(x,y) max(x,y) min
		mn=tbl[i];
		mx=tbl[pth[i][0]];

		int mnleft=minid(pth[i][0],mn);
		int mnrgt=minid(pth[i][1],mn);
		
		if (mnrgt<mnleft) {
			//min max(x,y) min(x,y)
			swap(tbl[i],tbl[pth[i][1]]);
		} else {
			//min min(x,y) max(x,y)
			swap(tbl[i],tbl[pth[i][0]]);
			swap(tbl[i],tbl[pth[i][1]]);
		}

	}
	for (int i=1;i<=n;i++) {
		printf("%d ",tbl[i]);
	}
	printf("\n");
	return 0;
}

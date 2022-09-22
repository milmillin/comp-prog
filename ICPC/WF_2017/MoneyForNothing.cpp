#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	int cost,day;
};

bool operator<(const ei &a, const ei &b) {
	if (a.day!=b.day) return a.day<b.day;
	return a.cost<b.cost;
}

vector<ei> sell;
vector<ei> buy;
typedef vector<ei>::iterator eit;
int ans;

int solve(eit sl,eit sr, eit bl, eit br) {
	//printf("%d %d\n",sl-sell.begin(),sr-sell.begin());
	if (sl+1==sr) {
		for (eit it=bl;it!=br;it++) {
			ans=max(ans,it->cost-sl->cost);
		}
		return sl->cost;
	}
	eit smid = sl+(sr-sl)/2;
	eit bmid = lower_bound(buy.begin(),br,ei{0,(smid-1)->day+1});
	int mn=2e9;
	//printf("%d %d\n",smid-sell.begin(),sr-sell.begin());
	mn=min(mn,solve(sl,smid,bmid,bl));
	mn=min(mn,solve(smid,sr,bl,bl));
	for (eit it=bl;it!=br;it++) {
		ans=max(ans,it->cost-mn);
	}
	return mn;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		sell.push_back(ei{a,b});
	}
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		buy.push_back(ei{a,b});
	}
	sort(sell.begin(),sell.end());
	sort(buy.begin(),buy.end());
	eit bmid = lower_bound(buy.begin(),buy.end(),ei{0,(sell.end()-1)->day+1});
	//printf("--%d\n",bmid-buy.begin());
	solve(sell.begin(),sell.end(),bmid,buy.end());
	printf("%d\n",ans);	
	return 0;
}

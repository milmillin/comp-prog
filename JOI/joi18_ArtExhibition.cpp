#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

long long sz[500100];
long long val[500100];

int main () {
	int n;
	scanf("%d",&n);
	long long a,b;
	vector<pair<long long,long long>> tbl;
	tbl.reserve(n);
	for (int i=0;i<n;i++) {
		scanf("%lld%lld",&a,&b);
		tbl.push_back({a,b});
	}
	sort(tbl.begin(),tbl.end());
	int nn=0;
	sz[0]=tbl[0].first;
	val[0]=tbl[0].second;
	
	for (int i=1;i<(int)tbl.size();i++) {
		if (tbl[i].first!=sz[nn]) {
			nn++;
			sz[nn]=tbl[i].first;
		}
		val[nn]+=tbl[i].second;
	}
	nn++;
	for (int i=1;i<nn;i++) {
		val[i]+=val[i-1];
	}

	long long mnn=-sz[0];
	long long ans=0;
	for (int i=0;i<nn;i++) {
		ans=max(ans,val[i]-sz[i]-mnn);
		mnn=min(mnn,val[i]-sz[i+1]);
	}
	printf("%lld\n",ans);
	return 0;
}

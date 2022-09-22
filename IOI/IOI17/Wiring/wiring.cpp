#include "wiring.h"
#include <cstdio>
#include <algorithm>

#ifdef debug
#include "grader.cpp"
#endif

using namespace std;

long long min_total_length(std::vector<int> r, std::vector<int> b) {
	vector<pair<int,bool>> tbl;
	tbl.reserve(r.size()+b.size());
	for (auto i:r) {
		tbl.push_back({i,false});
	}		
	for (auto i:b) {
		tbl.push_back({i,true});
	}
	sort(tbl.begin(),tbl.end());

	vector<vector<int>> block;
	block.push_back(vector<int>());
	block[0].push_back(tbl[0].first);
	vector<vector<long long>> pref;
	pref.push_back(vector<long long>());
	pref[0].push_back(tbl[0].first);
	for (int i=1;i<(int)tbl.size();i++) {
		if (tbl[i].second!=tbl[i-1].second) {
			block.push_back(vector<int>());
			pref.push_back(vector<long long>());
		}
		block.back().push_back(tbl[i].first);
		pref.back().push_back(tbl[i].first+(pref.back().empty()?0:pref.back().back()));
	}
	int m=block.size();
	vector<vector<long long>> dp(m);
	for (int i=0;i<m;i++) {
		dp[i].resize(block[i].size()+1);
		fill(dp[i].begin(),dp[i].end(),0);
		//printf("%d: ",i);
		//for (auto j:pref[i]) {
			//printf("%lld ",j);
		//}
		//printf("\n");
	}
	for (int i=m-1;i>=0;i--) {
		if (i<m-1) {
			dp[i][block[i].size()]=dp[i+1][0];
		}
		for (int j=block[i].size()-1;j>=0;j--) {
			dp[i][j]=1e18;
			if (i) {
				//single to left
				dp[i][j]=min(dp[i][j],dp[i][j+1]+block[i][j]-block[i-1].back());	
			}
			if (i<m-1) {
				//single to right
				dp[i][j]=min(dp[i][j],dp[i][j+1]+block[i+1].front()-block[i][j]);
				//whole lot to right
				if (block[i].size()-j<=block[i+1].size()) {
					dp[i][j]=min(dp[i][j],dp[i+1][block[i].size()-j]+pref[i+1][block[i].size()-j-1]-pref[i].back()+(j?pref[i][j-1]:0));
				}
			}
		}
	}
	//for (int i=0;i<m;i++) {
		//for (auto j:dp[i]) {
			//printf("%lld ",j);
		//}
		//printf("\n");
	//}
	//printf("--> %lld\n",dp[0][0]);
	return dp[0][0];
	//return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


int main () {
	int n;
	scanf("%d",&n);
	vector<pair<int,int> >inp(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&inp[i].first,&inp[i].second);
	}
	sort(inp.begin(),inp.end());
	vector<pair<int,int> >ans;
	int maxx=inp[0].second-inp[0].first;
	int gap=0;
	ans.push_back(inp[0]);
	for (int i=1;i<n;i++) {
		if (inp[i].first<=ans.back().second) {
			ans.back().second=max(ans.back().second,inp[i].second);
			maxx=max(maxx,ans.back().second-ans.back().first);
		}else {
			gap=max(gap,inp[i].first-ans.back().second);
			maxx=max(maxx,inp[i].second-inp[i].first);
			ans.push_back(inp[i]);
		}
	}
	printf("%d %d\n",maxx,gap);
	return 0;
}

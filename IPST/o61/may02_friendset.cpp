#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool comp(vector<int> &a, vector<int> &b) {
	if (a.size()!=b.size()) return false;
	for (int i=0;i<(int)a.size();i++) {
		if (a[i]!=b[i]) return false;
	}
	return true;
}

bool comp2(vector<int> &a, vector<int> &b, int x,int y) {
	if (a.size()!=b.size()) return false;
	vector<int> tmp;
	tmp.reserve(a.size());
	for (auto i:a) {
		if (i==x) continue;
		tmp.push_back(i);
	}
	vector<int> tmp2;
	tmp2.reserve(a.size());
	for (auto i:b) {
		if (i==y) continue;
		tmp2.push_back(i);
	}
	return tmp==tmp2;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	vector<vector<int>> pth(n);
	vector<pair<int,int>> ed;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		a--;
		b--;
		pth[a].push_back(b);
		pth[b].push_back(a);
		ed.push_back({a,b});
	}
	for (int i=0;i<n;i++) {
		sort(pth[i].begin(),pth[i].end());
	}

	long long ans=0;
	for (auto &i:ed) {
		if (comp2(pth[i.first],pth[i.second],i.second,i.first)) ans++;
	}

	sort(pth.begin(),pth.end());
	int last=0;
	for (int i=1;i<n;i++) {
		if (!comp(pth[i-1],pth[i])) {
			ans+=(long long)(i-last)*(i-last-1)/2;
			last=i;
		}
	}	
	ans+=(long long)(n-last)*(n-last-1)/2;
	printf("%lld\n",ans);
	return 0;
}

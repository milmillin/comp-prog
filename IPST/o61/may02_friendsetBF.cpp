#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

vector<int> pth[1010];

bool cmp(vector<int> &a,vector<int> &b,int m,int n) {
	int j=0;
	for (int i=0;i<(int)a.size();i++) {
		if (a[i]==m) continue;
		if (a[i]==n) continue;
		while (j<(int)b.size()&&(b[j]==m||b[j]==n)) j++;
		if (j==b.size()) return false;
		if (a[i]!=b[j]) return false;
		j++;
	}
	return true;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	assert(n<1000);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i=1;i<=n;i++) {
		sort(pth[i].begin(),pth[i].end());
	}
	int cnt=0;
	for (int i=1;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			if (pth[i].size()!=pth[j].size()) continue;
			if (!cmp(pth[i],pth[j],i,j)) continue;
			cnt++;	
		}
	}
	printf("%d\n",cnt);
	return 0;
}

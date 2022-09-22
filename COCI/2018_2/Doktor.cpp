#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int tbl[5000100];

struct aa {
	int mn,cnt;
};

map<int,int> mp;

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		mp[n-i+1-tbl[i]]++;
	}
	int mx=0;
	int mmm=-1;
	for (auto it:mp) {
		if (it.second>mx) {
			mx=it.second;
			mmm=it.first;
		}
	}
	int mn=2e9;
	mx=-1;
	for (int i=1;i<=n;i++) {
		if (n-i+1-tbl[i]==mmm) {
			mn=min(mn,min(i,tbl[i]));
			mx=max(mx,max(i,tbl[i]));	
		}
	}
	printf("%d %d\n",tbl[mn],tbl[mx]);
	return 0;
}

#include <cstdio>
#include <map>

using namespace std;

int sz[100100];
int par[100100];
int grp[100100];
map<int,int> mp;

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}



int main () {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=0;i<n;i++) {
		scanf("%d",&grp[i]);
		mp[grp[i]];
	}
	int cur=0;
	for (map<int,int>::iterator it=mp.begin();it!=mp.end();it++) {
		it->second=cur;
		cur++;
	}
	for (int i=0;i<n;i++) {
		grp[i]=mp[grp[i]];
	}
	
	return 0;
}

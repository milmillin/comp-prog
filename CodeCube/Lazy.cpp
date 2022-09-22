#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int,int> mp;

int tbl[100100];

vector<int> pos[100100];

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		mp[tbl[i]];
	}	
	int nn=1;
	for (auto &i:mp) {
		i.second=nn++;
	}
	for (int i=0;i<n;i++) {
		tbl[i]=mp[tbl[i]];
		pos[tbl[i]].push_back(i);
	}
	int a,b;
	int c;
	for (int i=0;i<q;i++) {
		scanf("%d%d%d",&a,&b,&c);
		a--;
		b--;
		c=mp[c];
		//printf("-- %d\n",c);
		printf("%d\n",upper_bound(pos[c].begin(),pos[c].end(),b)-lower_bound(pos[c].begin(),pos[c].end(),a));	
	}
	
	return 0;
}

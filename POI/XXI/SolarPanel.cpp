#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int comb(pair<int,int> a,pair<int,int> b) {
	int l=max(a.first,b.first);
	int r=min(a.second,b.second);
	if (l>r) return -1;
	return r;
}

vector<pair<int,int>> solve(int l,int r) {
	vector<pair<int,int>> a;
	vector<pair<int,int>> b;
	int j;
	for (int i=1;i*i<=r;i++) {
		//k==i
		a.push_back({l/i+(l%i?1:0),r/i});	
		//k==r/i
		j=r/i;
		b.push_back({l/j+(l%j?1:0),r/j});
	}
	reverse(a.begin(),a.end());
	b.insert(b.end(),a.begin(),a.end());
	return b;
}

void f() {
	int s1,s2,w1,w2;
	scanf("%d%d%d%d",&s1,&s2,&w1,&w2);		
	auto s=solve(s1,s2);
	auto w=solve(w1,w2);

	int ans=0;
	int j=0;
	for (int i=0;i<(int)w.size();i++) {
		while (j+1<(int)s.size()&&comb(s[j+1],w[i])!=-1) {
			j++;
		}
		ans=max(ans,comb(s[j],w[i]));
	}
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}

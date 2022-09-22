#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> pth[1010];
int col[1010];

struct edge {
	int a,b;
};

vector<edge> edges;

struct st {
	int x;
	int cnt1;
};

bool operator< (const st &a, const st &b) {
	return a.cnt1<b.cnt1;
}

int bitcnt(int x) {
	int cnt=0;
	while (x) {
		if (x%2) cnt++;
		x/=2;
	}
	return cnt;
}

int mic[1010][1050];
int mod=1000003;

int main () {
	int n,m,c;
	scanf("%d%d%d",&n,&m,&c);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		col[i]=1<<x;
		mic[i][col[i]]=1;
	}
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		edges.push_back(edge{a,b});
		//pth[a].push_back(b);
		//pth[b].push_back(a);
	}
	int endd=1<<c;
	vector<st> sts;
	for (int i=0;i<endd;i++) {
		sts.push_back(st{i,bitcnt(i)});
	}	
	sort(sts.begin(),sts.end());
	for (auto &s:sts) {
		if (s.cnt1==1) continue;
		for (auto &e:edges) {
			if ((s.x&col[e.a])==0) continue;
			if ((s.x&col[e.b])==0) continue;
			mic[e.a][s.x]+=mic[e.b][s.x^col[e.a]];
			mic[e.a][s.x]%=mod;
			mic[e.b][s.x]+=mic[e.a][s.x^col[e.b]];
			mic[e.b][s.x]%=mod;
		}
	}	
	int ans=0;
	for (int i=0;i<n;i++) {
		ans+=mic[i][endd-1];
		ans%=mod;
	}
	printf("%d\n",ans);
	return 0;
}


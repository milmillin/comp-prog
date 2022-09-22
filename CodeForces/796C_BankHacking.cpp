#include <cstdio>
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[300100];
int cnt[5];
vector<int> pth[300100];
bool visit[300100];

int mx=-2e9;
int ans=2e9;

void add(int x) {
	for (int j=0;j<3;j++) {
		if (x==mx+j) cnt[j]++;
	}
}

void rem(int x) {
	for (int j=0;j<3;j++) {
		if (x==mx+j) cnt[j]--;
	}
}

void setAns() {
	for (int i=2;i>=0;i--) {
		if (cnt[i]) {
			ans=min(ans,i+mx);
			//printf("ans: %d\n",ans);
			return;
		}
	}
}

void recur(int idx) {
	for (int i=0;i<(int)pth[idx].size();i++) {
		rem(tbl[pth[idx][i]]+2);
		add(tbl[pth[idx][i]]+1);
	}
	//printf("%d %d %d\n",cnt[0],cnt[1],cnt[2]);
	visit[idx]=true;
	setAns();
	rem(tbl[idx]);
	add(tbl[idx]+2);
	for (int i=0;i<(int)pth[idx].size();i++) {
		rem(tbl[pth[idx][i]]+1);
		add(tbl[pth[idx][i]]+2);
	}
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		rem(tbl[pth[idx][i]]+2);
		add(tbl[pth[idx][i]]);
		recur(pth[idx][i]);
		rem(tbl[pth[idx][i]]);
		add(tbl[pth[idx][i]]+2);
	}
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		mx=max(mx,tbl[i]);
	}
	for (int i=1;i<=n;i++) {
		add(tbl[i]+2);
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}

	rem(tbl[1]+2);
	add(tbl[1]);
	//printf("%d %d %d\n",cnt[0],cnt[1],cnt[2]);
	recur(1);
	printf("%d\n",ans);
	return 0;
}

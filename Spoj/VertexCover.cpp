#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<int> pth[100100];
bool visit[100100];

void dfs(int idx) {
	visit[idx]=true;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) {
			pth[idx][i]=0;
			continue;
		}
		dfs(pth[idx][i]);
	}
}

int mic[100100][2];

int dp(int idx, int st) {
	if (mic[idx][st]!=-1) return mic[idx][st];
	int ans0=0,ans1=0;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (!pth[idx][i]) continue;
		ans0+=min(dp(pth[idx][i],0),dp(pth[idx][i],1));
		ans1+=dp(pth[idx][i],1);
	}
	mic[idx][0]=ans1;
	mic[idx][1]=1+ans0;
	return mic[idx][st];
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(1);	
	memset(mic,-1,sizeof(mic));
	printf("%d\n",min(dp(1,0),dp(1,1)));
	return 0;
}

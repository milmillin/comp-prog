#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[300100];
bool visit[300100];
bool isMother[300100];
int dp[300100];
int low[300100];

void dep(int idx,int par,int d) {
	visit[idx]=true;
	dp[idx]=low[idx]=d;
	//int cur=0;
	//bool isArt=false;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		if (visit[pth[idx][i]]) {
			low[idx]=min(low[idx],dp[pth[idx][i]]);
			isMother[pth[idx][i]]=true;
			continue;
		}
		dep(pth[idx][i],idx,d+1);
		//cur++;
		//if (low[pth[idx][i]]>=dp[idx]) isArt=true;
		low[idx]=min(low[idx],low[pth[idx][i]]);
	}
	if (low[idx]<dp[idx]) isMother[idx]=true;
	//if ((par!=-1&&isArt)||(par==-1&&cur>1)) {
		//isMother[idx]=true;	
	//}
}

int dfs(int idx,int par) {
	int cnt=1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		if (isMother[pth[idx][i]]) continue;
		cnt+=dfs(pth[idx][i],idx);
	}
	return cnt;
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i=0;i<300100;i++) {
		if (!visit[i]) dep(i,-1,0);
	}
	for (int i=0;i<300100;i++) {
		if (isMother[i]) {
			int cnt=dfs(i,-1);
			printf("%d %d\n",i,cnt-1);
		}
	}
	return 0;
}

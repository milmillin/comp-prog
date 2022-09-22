#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[300100];
bool visit[300100];
//bool isMom[300100];

int dep(int idx,int par) {
	visit[idx]=true;
	int cur=-1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		if (visit[pth[idx][i]]) {
			//printf("%d %d\n",idx,dfs(idx,-1)-1);
			//isMom[idx]=true;
			return pth[idx][i];
		}
		cur=max(cur,dep(pth[idx][i],idx));
	}
	if (cur!=-1) {
		//isMom[idx]=true;
	}
	if (cur!=idx) return cur;
	return -1;
}

int dfs(int idx,int par) {
	int cnt=1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		//if (isMom[pth[idx][i]]) continue;
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
		if (!visit[i]) dep(i,-1);
	}
	for (int i=0;i<300100;i++) {
		//if (isMom[i]) {
			int cnt=dfs(i,-1);
			printf("%d %d\n",i,cnt-1);
		//}
	}
	return 0;
}

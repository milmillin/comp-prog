#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int pos[5010];
int cost[100100];
int mic[5010];

int dp(int idx) {
	if (mic[idx]!=-1) return mic[idx];
	//printf("\n--%d\n",idx);
	int mn=cost[pos[idx]-pos[0]+1];
	//printf("--- %d\n",mn);
	for (int i=0;i<idx;i++) {
		mn=min(mn,dp(i)+cost[pos[idx]-pos[i+1]+1]);
	}
	return mic[idx]=mn;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&pos[i]);
	}
	sort(pos,pos+n);
	for (int i=1;i<=m;i++) {
		scanf("%d",&cost[i]);
	}
	for (int i=m-1;i>=1;i--) {
		cost[i]=min(cost[i],cost[i+1]);
	}
	memset(mic,-1,sizeof(mic));
	//for (int i=0;i<n;i++) {
		//printf("%d ",dp(i));
	//}
	//printf("\n");
	printf("%d\n",dp(n-1));
	return 0;
}

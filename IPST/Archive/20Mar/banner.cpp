#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> tbl[500];
int mic[500][500];
int cnt[500][500];
int n,k;

int dp(int st,int end) {
	if (mic[st][end]!=-1) return mic[st][end];
	int ans=0;
	for (int i=st+1;i<end;i++) {
		ans=max(ans,dp(st,i)+dp(i+1,end));
	}
	return mic[st][end]=cnt[st][st]+cnt[end][end]+cnt[st][end]+ans;
}

int main () {
	scanf("%d%d",&n,&k);
	int a,b;
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		//tbl[b].push_back(a);
		cnt[a][b]++;
	}
	memset(mic,-1,sizeof(mic));
	printf("%d\n",k-dp(1,n));
	//for (int i=1;i<=n;i++) {
		//for (int j=1;j<=n;j++) {
			//printf("%d ",dp(i,j));
		//}
		//printf("\n");
	//}
	return 0;
}

#include <cstdio>
#include <algorithm>

using namespace std;

int freq[1010];
int ask[1010];
int num[1010];
int ncr[1010][1010];

void init() {
	ncr[0][0]=1;
	ncr[1][0]=1;
	ncr[1][1]=1;
	for (int i=2;i<1010;i++) {
		ncr[i][0]=1;
		for (int j=1;j<=min(i,1000);j++) {
			ncr[i][j]=ncr[i-1][j]+ncr[i-1][j-1];
			ncr[i][j]%=9901;
			//printf("%d ",ncr[i][j]);
		}
		//printf("\n");
	}
}


int main () {
	init();
	int n,m,sum=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&freq[i]);
		sum+=freq[i];
	}
	int curAmt=0;
	int cur=0;
	ask[0]=1;
	num[0]=1;
	for (int i=1;i<=m;i++) {
		scanf("%d",&ask[i]);
		while (curAmt<ask[i]) {
			cur++;
			curAmt+=freq[cur];
		}
		num[i]=cur;
	}
	ask[m+1]=sum;
	num[m+1]=n;
	//int last=0;
	int way=1;
	for (int i=1;i<=m+1;i++) {
		if (num[i]==num[i-1]) continue;
		//printf("%d %d\n",ask[i]-ask[i-1],num[i]-num[i-1]);
		way*=ncr[ask[i]-ask[i-1]][num[i]-num[i-1]];
		way%=9901;
	}
	printf("%d\n",way);
	return 0;
}

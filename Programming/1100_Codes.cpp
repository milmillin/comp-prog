#include <cstdio>

using namespace std;

long long cnt[11][11][11];

int main() {
	int n;
	scanf("%d",&n);
	char x[5];
	for (int i=0;i<n;i++) {
		scanf("%s",x);
		cnt[x[0]-'0'][10][10]++;
		cnt[10][x[1]-'0'][10]++;
		cnt[10][10][x[2]-'0']++;
		cnt[x[0]-'0'][x[1]-'0'][10]++;
		cnt[x[0]-'0'][10][x[2]-'0']++;
		cnt[10][x[1]-'0'][x[2]-'0']++;
		cnt[x[0]-'0'][x[1]-'0'][x[2]-'0']++;
	}

	for (int i=0;i<11;i++) {
		for (int j=0;j<11;j++) {
			for (int k=0;k<11;k++) {
				cnt[i][j][k]=cnt[i][j][k]*(cnt[i][j][k]-1)/2;
			}
		}
	}
	long long ans=0;
	long long sum;
	for (int i=0;i<10;i++) {
		for (int j=0;j<10;j++) {
			for (int k=0;k<10;k++) {
				ans+=cnt[i][j][k];
				cnt[i][10][10]-=cnt[i][j][k];
				cnt[10][j][10]-=cnt[i][j][k];
				cnt[10][10][k]-=cnt[i][j][k];
				cnt[i][j][10]-=cnt[i][j][k];
				cnt[i][10][k]-=cnt[i][j][k];
				cnt[10][j][k]-=cnt[i][j][k];
			}
		}
	}
	for (int i=0;i<10;i++) {
		for (int j=0;j<10;j++) {
			ans+=cnt[i][j][10];
			cnt[i][10][10]-=cnt[i][j][10];
			cnt[10][j][10]-=cnt[i][j][10];
			ans+=cnt[i][10][j];
			cnt[i][10][10]-=cnt[i][10][j];
			cnt[10][10][j]-=cnt[i][10][j];
			ans+=cnt[10][i][j];
			cnt[10][i][10]-=cnt[10][i][j];
			cnt[10][10][j]-=cnt[10][i][j];
		}
	}
	for (int i=0;i<10;i++) {
		ans+=cnt[i][10][10]+cnt[10][i][10]+cnt[10][10][i];
	}
	printf("%lld\n",ans);
	return 0;
}

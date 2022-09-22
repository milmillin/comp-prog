#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int tbl[20][20];
int dp[20][8200];

int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}
	memset(dp,63,sizeof(dp));
	for (int i=0;i<n;i++) dp[i][1<<i]=0;
	int m=1<<n;
	for (int config=1;config<m;config++) {
		vector<int> cur;
		for (int i=0;i<n;i++) {
			if ((1<<i)&config) cur.push_back(i);
		}
		int cm=1<<(int)cur.size();
		for (int child=1;child<cm;child++) {
			vector<int> chd;
			int childconfig=0;
			for (int i=0;i<n;i++) {
				if ((1<<i)&child) {
					childconfig^=1<<cur[i];
					chd.push_back(cur[i]);
				}
			}
			for (auto dad:cur) {
				if ((1<<dad)&childconfig) continue;
				for (auto c:chd) {
					dp[dad][config]=min(dp[dad][config],max(dp[dad][config^childconfig],dp[c][childconfig])+tbl[dad][c]);
				}
			}
		}
	}
	printf("%d\n",dp[0][(1<<n)-1]);
	return 0;
}

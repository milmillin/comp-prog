#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1000000007;


long long solve(int st, const vector<vector<int>> &tbl) {
	int n = tbl.size();
	int m = tbl[0].size();
	int key;
	vector<int> mask(31, 0);
	vector<vector<long long>> dp(n + 1, vector<long long>(1 << 16, 0));
	mask[0] = -1;
	for (int j = 0; j < (1 << (m / 2 + 1)); j++) {
		dp[0][j] = 1;
	}
	for(int i=0;i<n;i++)
	{
		key=0;
		mask[i + 1] = 0;
		if ((i + st) % 2 == 0) {
			for (int j = 0; j < m / 2; j++) {
				key<<=1;
				mask[i + 1] <<= 1;
				mask[i + 1] ^= 1;
				if(tbl[i][j*2 + 1]==1)
				{
					key^=1;
				}
				else if(tbl[i][j*2 + 1]==-1)
				{
					mask[i + 1] ^= 1;
				}
			}
			for(int j=0;j<(1<<(m-m/2));j++)
			{
				dp[i + 1][(key^(j>>1)^j)&mask[i + 1]] += dp[i][j&(mask[i])];
				dp[i + 1][(key^(j>>1)^j)&mask[i + 1]] %= mod;
			}
		} else {
			for (int j = 0; j < m - m / 2; j++) {
				key<<=1;
				mask[i + 1] <<= 1;
				mask[i + 1] ^= 1;
				if(tbl[i][j*2]==1)
				{
					key^=1;
				}
				else if(tbl[i][j*2]==-1)
				{
					mask[i + 1] ^= 1;
				}
			}
			for(int j=0;j<(1<<(m/2));j++)
			{
				dp[i + 1][(key^(j<<1)^j)&mask[i + 1]] += dp[i][j&(mask[i])];
				dp[i + 1][(key^(j<<1)^j)&mask[i + 1]] %= mod;
			
			}
		}
	}
	return dp[n][0];
}


void f() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<vector<int>> tbl(n, vector<int>(m));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&tbl[i][j]);
		}
	}
	printf("%lld\n", (solve(0, tbl) * solve(1, tbl)) % mod);
}

int main()
{
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

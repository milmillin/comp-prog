#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

vector<int> pos[100100];

long long dp[100100];

int main () {
	int n;
	scanf("%d", &n);
	int x;
	for (int i = 0; i < 2 * n; i++) {
		scanf("%d", &x);
		pos[x].push_back(i);
	}

	dp[1] = pos[1][0] + pos[1][1];
	for (int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + min(abs(pos[i][0] - pos[i - 1][0]) + abs(pos[i][1] - pos[i - 1][1]),
				abs(pos[i][0] - pos[i - 1][1]) + abs(pos[i][1] - pos[i - 1][0]));
	}

	printf("%lld\n", dp[n]);
	return 0;
}

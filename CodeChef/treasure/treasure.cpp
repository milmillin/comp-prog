#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1000000007;

const int LEFT = 1;
const int BOT = 2;
const int RIGHT = 4;

bool have(const int val, int st) {
	return (st & val) == val;
}

bool get(int k, int sz, int pos) {
	if (pos == 0) return false;
	if (pos == sz + 1) return false;
	return (k & (1 << (pos - 1))) == (1 << (pos - 1));
}

void f() {
	int r, c;
	scanf("%d%d", &r, &c);
	vector<vector<int>> tbl(r + 1, vector<int>(c + 1, 0));
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			scanf("%d", &tbl[i][j]);
		}
	}

	vector<vector<vector<long long>>> dp(r + 1, 
			vector<vector<long long>>(c + 2,
				vector<long long>(8, 0)));

	//init table border
	for (int i = 1; i <= r; i++) {
		dp[i][0][0] = 1;
		dp[i][0][RIGHT] = 1;
		dp[i][c + 1][0] = 1;
		dp[i][c + 1][LEFT] = 1;
	}
	for (int j = 1; j <= c; j++) {
		dp[0][j][0] = 1;
		dp[0][j][BOT] = 1;
	}
	dp[0][0][0] = 1;
	dp[0][c + 1][0] = 1;

	//dp
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			for (int st1 = 0; st1 < 8; st1++) {
				for (int st2 = 0; st2 < 8; st2++) {
					if (have(RIGHT, st1) != have(LEFT, st2)) continue;
					int cnt = 0;
					int newSt = 0;
					if (have(RIGHT, st1)) cnt++;
					if (have(BOT, st1)) {
						cnt++;
						newSt ^= LEFT;
					}
					if (have(BOT, st2)) {
						cnt++;
						newSt ^= RIGHT;
					}
					if (tbl[i][j] == -1) {
						// any
						dp[i][j][newSt] += (dp[i - 1][j - 1][st1] * dp[i - 1][j + 1][st2]) % mod;
						dp[i][j][newSt ^ BOT] += (dp[i - 1][j - 1][st1] * dp[i - 1][j + 1][st2]) % mod;
						//printf("yay %d %d %d %lld\n", i, j, newSt, dp[i][j][newSt]);
						//printf("yay %d %d %d %lld\n", i, j, newSt ^ BOT, dp[i][j][newSt ^ BOT]);
					} else {
						if ((cnt % 2) != tbl[i][j]) newSt ^= BOT;
						dp[i][j][newSt] += (dp[i - 1][j - 1][st1] * dp[i - 1][j + 1][st2]) % mod;
						//printf("yay %d %d %d %lld\n", i, j, newSt, dp[i][j][newSt]);
					}
				}
			}
		}
	}

	int lim1 = 1 << (c / 2);
	
	long long ans1 = 0;
	for (int k = 0; k < lim1; k++) {
		long long curAns = 1;
		for (int j = 1; j <= c; j += 2) {
			int st = 0;
			if (get(k, c / 2, j / 2)) st ^= LEFT;
			if (get(k, c / 2, j / 2 + 1)) st ^= RIGHT;
			curAns *= dp[r][j][st];
			curAns %= mod;
		}
		ans1 += curAns;
		ans1 %= mod;
	}


	int lim2 = 1 << (c / 2 + (c % 2));
	long long ans2 = 0;
	for (int k = 0; k < lim2; k++) {
		long long curAns = 1;
		for (int j = 2; j <= c; j += 2) {
			int st = 0;
			if (get(k, c / 2 + (c % 2), j / 2)) st ^= LEFT;
			if (get(k, c / 2 + (c % 2), j / 2 + 1)) st ^= RIGHT;
			curAns *= dp[r][j][st];
			curAns %= mod;
		}
		ans2 += curAns;
		ans2 %= mod;
	}
	//printf("%lld %lld\n", ans1, ans2);
	printf("%lld\n", (ans1 * ans2) % mod);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

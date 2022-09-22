#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> pos[5010];

int mx[20100];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		if (b < a) b += n;
		pos[a].push_back(b);
	}
	for (int i = 1; i <= n; i++) {
		sort(pos[i].begin(), pos[i].end(), [](const int &a, const int &b) {
				return a > b;
				});
	}
	for (int i = 1; i <= n; i++) {
		memset(mx, 0, sizeof(mx));
		int mxk = 0;
		for (int j = 1; j < i; j++) {
			mxk = max(mxk, (int)pos[j].size());
			for (int k = 0; k < (int)pos[j].size(); k++) {
				mx[k] = max(mx[k], pos[j][k] - i + n);
			}
		}
		for (int j = i; j <= n; j++) {
			mxk = max(mxk, (int)pos[j].size());
			for (int k = 0; k < (int)pos[j].size(); k++) {
				mx[k] = max(mx[k], pos[j][k] - i);
			}
		}
		long long ans = 0;
		for (int k = 0; k < mxk; k++) {
			ans = max(ans, (long long)k * n + mx[k]);
		}
		printf("%lld ", ans);
	}
	printf("\n");
	return 0;
}

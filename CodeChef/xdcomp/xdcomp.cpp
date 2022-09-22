#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int n, x;
int a[100100];
int sum[100100];
vector<int> pth[100100];

const int mod = 1000000007;

struct pp {
	long long o, x;
};

inline long long add (long long a, long long b) {
	return (a + b) % mod;
}

inline long long mul (long long a, long long b) {
	return (a * b) % mod;
}

pp solve (int idx, int par) {
	pp ans{1ll, 0ll};
	sum[idx] = a[idx];
	for (auto i: pth[idx]) {
		if (i == par) continue;
		pp tmp2 = solve(i, idx);
		sum[idx] ^= sum[i];
		pp tmp{tmp2.o, tmp2.x};
		if (sum[i] == 0) {
			tmp.o = add(tmp2.o, tmp2.x);
		} 
		if (sum[i] == x) {
			tmp.x = add(tmp2.x, tmp2.o);
		} 
		ans = pp{add(mul(ans.o, tmp.o), mul(ans.x, tmp.x)),
			add(mul(ans.o, tmp.x), mul(ans.x, tmp.o))};
	}
	return ans;
}

int main () {
	scanf("%d%d", &n, &x);
	//assert(x != 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	pp res = solve(1, 1);
	if (sum[1] != 0 && sum[1] != x) {
		printf("0\n");
	} else if (x == 0) {
		printf("%lld\n", add(res.o, res.x));
	} else if (sum[1] == 0) {
		printf("%lld\n", res.x);
	} else if (sum[1] == x) {
		printf("%lld\n", res.o);
	}
	return 0;
}

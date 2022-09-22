#include <cstdio>

using namespace std;

int spf[2000100];

int cnt[2000100];

void init() {
	for (int i = 1; i < 2000100; i++) spf[i] = i;
	for (int i = 4; i < 2000100; i += 2) spf[i] = 2;
	for (int i = 3; i < 2000100; i += 2) {
		if (spf[i] != i) continue;
		if (i > 2000) break;
		for (int j = i * i; j < 2000100; j += i) {
			if (spf[j] == j) spf[j] = i;
		}
	}
}

void add(int x) {
	while (x != 1) {
		cnt[spf[x]]++;
		x /= spf[x];
	}
}

void del(int x,int amt) {
	while (x != 1) {
		cnt[spf[x]]-=amt;
		x /= spf[x];
	}
}

int n, m;
long long poww(int b, int x) {
	if (x == 0) return 1;
	if (x == 1) return b;
	long long a = poww(b, x / 2);
	a *= a;
	a %= m;
	if (x%2) return (a * b)%m;
	return a;
}

int main () {
	init();
	scanf("%d%d", &n, &m);
	for (int i = n+1; i <= 2 * n; i++) {
		add(i);
	}
	for (int i = 2; i <= n; i++) {
		del(i,1);
	}
	long long ans = 1;
	for (int i = 2; i < 2000100; i++) {
		ans *= poww(i, cnt[i] * 2);
		ans %= m;
	}
	printf("%lld\n", ans);
	return 0;
}

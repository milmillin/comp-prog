#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void f() {
	string x;
	cin >> x;
	int n = x.size();
	vector<int> cnt(26, 0);
	for (auto c : x) {
		cnt[c - 'A']++;
	}
	sort(cnt.begin(), cnt.end());
	reverse(cnt.begin(), cnt.end());
	int ans = n;
	for (int i = 1; i <= 26; i++) {
		if (n % i != 0) continue;
		int want = n / i;
		int cur = 0;
		for (int j = 0; j < i; j++) {
			cur += max(0, want - cnt[j]);
		}
		ans = min(ans, cur);
	}
	printf("%d\n", ans);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

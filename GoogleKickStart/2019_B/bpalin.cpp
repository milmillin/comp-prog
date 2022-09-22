#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

void f() {
	int n, q;
	scanf("%d%d", &n, &q);
	string x;
	cin >> x;
	vector<vector<int>> tbl(26, vector<int>(n + 1, 0));
	for (int i = 0; i < n; i++) {
		tbl[x[i] - 'A'][i + 1]++;
		for (int j = 0; j < 26; j++) {
			tbl[j][i + 1] += tbl[j][i];
		}
	}

	int cntYes = 0;
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int even = 0;
		int odd = 0;
		for (int i = 0; i < 26; i++) {
			if ((tbl[i][r] - tbl[i][l - 1]) % 2) odd++;
			else even++;
		}
		if (odd <= 1) cntYes++;
	}
	printf("%d\n", cntYes);
	fflush(stdout);
}

int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		f();
	}
	return 0;
}

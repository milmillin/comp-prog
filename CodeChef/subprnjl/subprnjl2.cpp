#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void f() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> tbl(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tbl[i]);
	}
	int cnt = 0;
	int eiei = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (tbl[j] == 1) eiei++;
			if (eiei) cnt++;
		}
		eiei = 0;
	}
	


}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}

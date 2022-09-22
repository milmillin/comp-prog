#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxv = 700000;

bool prime[maxv];
vector<int> prm;
vector<int> odd;
vector<int> even; 

void init() {
	prime[2] = true;
	for (int i = 3; i < maxv; i++) {
		prime[i] = true;
	}
	for (int i = 3; i < maxv; i += 2) {
		if (!prime[i]) continue;
		for (int j = i * 2; j < maxv; j += i) {
			prime[j] = false;
		}
	}
	prm.push_back(2);
	for (int i = 3; i < maxv; i += 2) {
		if (prime[i]) {
			prm.push_back(i);
		}
	}
	for (int i = 0; i < 4; i++) {
		even.push_back(prm[i]);
	}
	for (int i = 4; i + 1 < (int)prm.size(); i += 2) {
		even.push_back(3);
		even.push_back(prm[i]);
		even.push_back(5);
		even.push_back(prm[i + 1]);
	}
	for (int i = 0; i < 5; i++) {
		odd.push_back(prm[i]);
	}
	for (int i = 5; i + 1 < (int)prm.size(); i += 2) {
		odd.push_back(3);
		odd.push_back(prm[i]);
		odd.push_back(5);
		odd.push_back(prm[i + 1]);
	}
}

void gen(int n, vector<int> &tbl) {
	printf("%d ", tbl[0] * tbl[n - 1]);
	for (int i = 1; i < n; i++) {
		printf("%d ", tbl[i] * tbl[i - 1]);
	}
	printf("\n");
}

void f() {
	int n;
	scanf("%d", &n);
	if (n <= 3000) {
		gen(n, prm);
	} else if (n % 2) {
		gen(n, odd);
	} else {
		gen(n, even);
	}
}

int main () {
	init();
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

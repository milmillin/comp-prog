#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void f() {
	int n;
	scanf("%d", &n);
	n = 2 * n - 2;
	string x;
	cin >> x;
	for (int i = 0; i < n; i++) {
		if (x[i] == 'S') x[i] = 'E';
		else x[i] = 'S';
	}
	cout << x << '\n';
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

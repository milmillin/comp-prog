#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void f() {
	string x;
	cin >> x;
	
	string a = x;
	string b = x;

	int n = (int)x.size();
	for (int i = 0; i < n; i++) {
		if (x[i] == '4') {
			a[i] = '1';
			b[i] = '3';
		} else {
			a[i] = '0';
		}
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	while (a.back() == '0') a.pop_back();
	while (b.back() == '0') b.pop_back();
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	cout << a << ' ' << b << '\n';
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

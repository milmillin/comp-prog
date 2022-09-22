#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct ei {
	int val;
	int pos;
};

int main () {
	int n;
	scanf("%d", &n);
	vector<string> tbl;
	tbl.reserve(n);
	string x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		tbl.push_back(x);
	}




	return 0;
}

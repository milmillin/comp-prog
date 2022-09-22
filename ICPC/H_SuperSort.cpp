#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmpNeg(const string &a, const string &b) {
	
}

int main () {
	int n;
	scanf("%d",&n);
	vector<string> neg;
	vector<string> pos;
	string x;
	for (int i=0;i<n;i++) {
		cin >> x;
		if (x[0]=='-') {
			int cur=1;
			for (;x[cur]==0;cur++) {}
			neg.push_back(x.substr(cur,string::npos));
		} else {
			int cur=0;
			for (;x[cur]==0;cur++) {}
			pos.push_back(x.substr(cur,string::npos));
		}
	}
	return 0;
}

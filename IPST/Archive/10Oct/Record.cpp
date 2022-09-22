#include <map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

map<vector<string>,int> mm;

int main () {
	int n;
	scanf("%d",&n);
	string x;
	vector<string> a;
	int maxx=0;
	for (int i=0;i<n;i++) {
		a.clear();
		for (int j=0;j<3;j++) {
			cin>>x;
			a.push_back(x);
		}
		sort(a.begin(),a.end());
		maxx=max(maxx,++mm[a]);
	}
	printf("%d\n",maxx);
	return 0;
}

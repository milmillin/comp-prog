#include <cstdio>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

map<string,int> mp;
vector<string> inp;

int main () {
	int n;
	scanf("%d",&n);
	string x;
	for (int i=0;i<n;i++) {
		cin>>x;
		inp.push_back(x);
		//printf("%d\n",x.length());
		set<string> st;
		for (int j=0;j<(int)x.length();j++) {
			for (int k=j;k<(int)x.length();k++) {
				//printf("-- %d\n",j);
				st.insert(x.substr(j,k-j+1));
				//mp[x.substr(j,k-j+1)]++;
			}
		}
		for (auto &a:st) {
			mp[a]++;
		}
	}
	int cnt=0;
	for (auto &a: inp) {
		cnt+=mp[a]-1;
		//printf("%d\n",mp[a]);
	}
	printf("%d\n",cnt);
	return 0;
}

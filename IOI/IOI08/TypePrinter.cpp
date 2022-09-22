#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

vector<string> tbl;
vector<char> ans;
map<string,int> mp;

bool cmp(const string &a ,const string &b) {
	string x;
	int cur=0;
	while (a[cur]==b[cur]) {
		x.push_back(a[cur]);
		cur++;		
	}
	string y=x;
	if (a[cur]) x.push_back(a[cur]);
	if (b[cur]) y.push_back(b[cur]);
	//cout << x << " " << y << " " << mp[x] << " " << mp[y] << endl;
	int aa=mp[x];
	int bb=mp[y];
	if (aa!=bb) return aa<bb;
	return x<y;
}

int main () {
	int n;
	scanf("%d",&n);
	string x;
	string y;
	for (int i=0;i<n;i++) {
		cin >> x;
		tbl.push_back(x);
		y.clear();
		for (int j=0;j<(int)x.size();j++) {
			y.push_back(x[j]);
			mp[y]=max(mp[y],(int)x.size());
		}
	}
	sort(tbl.begin(),tbl.end(),cmp);
	for (int i=0;i<(int)tbl[0].size();i++) {
		ans.push_back(tbl[0][i]);
	}
	ans.push_back('P');
	for (int i=1;i<n;i++) {
		int cnt=0;
		while (tbl[i][cnt]==tbl[i-1][cnt]) cnt++;
		for (int j=0;j<(int)tbl[i-1].size()-cnt;j++) {
			ans.push_back('-');
		}
		for (int j=cnt;j<(int)tbl[i].size();j++) {
			ans.push_back(tbl[i][j]);
		}
		ans.push_back('P');
	}
	printf("%d\n",ans.size());
	for (int i=0;i<(int)ans.size();i++) {
		printf("%c\n",ans[i]);
	}
	return 0;
}

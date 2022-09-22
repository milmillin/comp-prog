#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool next(vector<int> &cur,const vector<vector<char>> &work) {
	int l=work.size();
	for (int i=l-1;i>=0;i--) {
		if (cur[i]+1<work[i].size()) {
			cur[i]++;
			return true;
		}
		cur[i]=0;
	}	
	return false;
}

string toString(const vector<int> &cur, const vector<vector<char>> &work) {
	string tmp;
	int l=work.size();
	for (int i=0;i<l;i++) {
		tmp.push_back(work[i][cur[i]]);
	}
	return tmp;
}

void f() {
	int n,l;
	scanf("%d%d",&n,&l);
	vector<string> tbl(n);
	vector<vector<char>> work(l);
	for (int i=0;i<n;i++) {
		cin >> tbl[i];
		for (int j=0;j<l;j++) {
			work[j].push_back(tbl[i][j]);
		}
	}
	sort(tbl.begin(),tbl.end());
	for (int i=0;i<l;i++) {
		sort(work[i].begin(),work[i].end());
		work[i].erase(unique(work[i].begin(),work[i].end()),work[i].end());
	}
	vector<int> cur(l,0);	
	int ptr=0;
	while (ptr<n&&toString(cur,work)==tbl[ptr]) {
		if (!next(cur,work)) {
			printf("-\n");
			return;
		}
		string tmp = toString(cur,work);
		while (ptr<n&&tmp>tbl[ptr]) {
			ptr++;
			//if (ptr==n) {
				//printf("-\n");
				//return;
			//}
		}
	}
	if (toString(cur,work)==tbl[ptr]) {
		printf("--\n");
		return;
	}
	printf("%s\n",toString(cur,work).c_str());
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}

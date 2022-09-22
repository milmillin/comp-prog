#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct fk {
	char x;
	int num;
	bool ext;
};

void f() {
	string x,y;
	cin>>x;
	cin>>y;
	vector<fk> tbl;
	
	int a=0,b=0;
	char last=0;
	while (a<x.size()) {
		if (a+1 < (int) x.size() && x[a+1]=='*') {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],0,true});
			} else {
				tbl.back().ext|=true;
			}
			last=x[a];
			a+=2;
		} else if (a+1 < (int) x.size() && x[a+1]=='+') {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],1,true});
			} else {
				tbl.back().num++;
				tbl.back().ext|=true;
			}
			last=x[a];
			a+=2;
		} else {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],1,false});
			} else {
				tbl.back().num++;
			}
			last=x[a];
			a++;
		}
	}

	for (int i=0;i<(int)tbl.size();i++) {
		for (int j=0;j<tbl[i].num;j++) {
			if (y[b]!=tbl[i].x) {
				printf("NO\n");
				return;
			}
			b++;
		}
		if (tbl[i].ext) {
			while (y[b]==tbl[i].x) b++;
		}
	}
	if (b==y.size()) printf("YES\n");
	else printf("NO\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool cmp (const vector<string> &a, const vector<string> &b) {
	return a.size()>b.size();
}

void f() {
	vector<vector<string> > tbl(3); // r y b
	int n,r,o,y,g,b,v;
	scanf("%d%d%d%d%d%d%d",&n,&r,&o,&y,&g,&b,&v);
	if (y<v||r<g||b<o) {
		printf("IMPOSSIBLE\n");
		return;
	}
	if (y>0&&y==v&&o+g+r+b>0) {
		printf("IMPOSSIBLE\n");
		return;
	}
	if (r>0&&r==g&&o+y+v+b>0) {
		printf("IMPOSSIBLE\n");
		return;
	}
	if (b>0&&b==o&&y+g+r+v>0) {
		printf("IMPOSSIBLE\n");
		return;
	}
	
	string xxx="";
	int yyy;
	if (y&&y==v) {xxx="YV";yyy=y;}
	if (r&&r==g) {xxx="RG";yyy=r;}
	if (b&&b==o) {xxx="BO";yyy=b;}
	//printf("YAY\n");
	//cout << xxx << endl;
	if (xxx.size()) {
		for (int i=0;i<yyy;i++) {
			cout << xxx;
		}
		printf("\n");
		return;
	}
	

	//R
	if (r) {
		string rg="R";
		for (int i=0;i<g;i++) {
			rg+="GR";
		}
		r-=g+1;
		tbl[0].push_back(rg);
		for (int i=0;i<r;i++) {
			tbl[0].push_back("R");
		}
	}

	//Y
	if (y) {
		string yv="Y";
		for (int i=0;i<v;i++) {
			yv+="VY";
		}
		y-=v+1;
		tbl[1].push_back(yv);
		for (int i=0;i<y;i++) {
			tbl[1].push_back("Y");
		}
	}

	//B
	if (b) {
		string bo="B";
		for (int i=0;i<o;i++) {
			bo+="OB";
		}
		b-=o+1;
		tbl[2].push_back(bo);
		for (int i=0;i<b;i++) {
			tbl[2].push_back("B");
		}
	}
	sort(tbl.begin(),tbl.end(),cmp);

	if (tbl[1].size()+tbl[2].size()<tbl[0].size()) {
		printf("IMPOSSIBLE\n");
		return;
	}
	vector<string> &AA=tbl[0],&BB=tbl[1],&CC=tbl[2];
	int tmp = AA.size()-CC.size();
	for (int i=0;i<AA.size();i++) {
		cout << AA[i];
		if (i<BB.size()) cout << BB[i];
		if (i>=tmp) cout << CC[i-tmp];
	}
	printf("\n");
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

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int scr[30];

struct ei {
	int ans,idx,tme;
};

struct ai {
	int idx, scr;
};

int ans;

bool cmp2 (const ai &a, const ai &b) {
	if (a.scr!=b.scr) return a.scr>b.scr;
	return a.idx<b.idx;
}

bool cmp (const ei &a, const ei &b) {
	if (abs(a.ans-ans)!=abs(b.ans-ans)) return abs(a.ans-ans)<abs(b.ans-ans);
	return a.tme<b.tme;
}

int main () {
	int n,r;
	scanf("%d%d",&n,&r);
	for (int i=0;i<r;i++) {
		int nn;
		scanf("%d%d",&ans,&nn);
		char a;
		int b;
		vector<ei> tbl;
		for (int j=0;j<nn;j++) {
			scanf(" %c%d",&a,&b);
			tbl.push_back(ei{b,a-'A',j});
		}
		sort(tbl.begin(),tbl.end(),cmp);
		for (int j=0;j<min(3,(int)tbl.size());j++) {
			scr[tbl[j].idx]+=3-j;
			if (tbl[j].ans==ans) scr[tbl[j].idx]+=3;
		}
	}
	vector<ai> anss;
	for (int i=0;i<n;i++) {
		anss.push_back(ai{i,scr[i]});
	}
	sort(anss.begin(),anss.end(),cmp2);
	printf("%d %c ",anss[0].scr,anss[0].idx+'A');
	for (int i=1;i<n;i++) {
		if (anss[i].scr==anss[i-1].scr) {
			printf("%c ",anss[i].idx+'A');
		} else {
			printf("\n%d %c ",anss[i].scr,anss[i].idx+'A');
		}
	}
	printf("\n");
	return 0;
}

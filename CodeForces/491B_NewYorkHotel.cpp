#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct pnt {
	int x,y;
};

int maxX=0,maxY=0,minX=2e9,minY=2e9;

bool cmp (const pnt &a, const pnt &b) {
	return a.y-a.x<b.y-b.x;
}

bool cmp2 (const pnt &a, const pnt &b) {
	return a.y+a.x<b.y+b.x;
}

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	int n;
	scanf("%d",&n);
	vector<pnt> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].x,&tbl[i].y);
	}
	sort(tbl.begin(),tbl.end(),cmp);
	vector<pnt> chk;
	chk.push_back(tbl.front());
	chk.push_back(tbl.back());
	sort(tbl.begin(),tbl.end(),cmp2);
	chk.push_back(tbl.front());
	chk.push_back(tbl.back());
	int q;
	scanf("%d",&q);
	int ans=2e9;
	int ansId=-1;
	int aa,bb;
	for (int i=1;i<=q;i++) {
		scanf("%d%d",&aa,&bb);
		int mx=-1;
		for (int j=0;j<4;j++) {
			mx=max(mx,abs(aa-chk[j].x)+abs(bb-chk[j].y));
		}
		if (mx<ans) {
			ans=mx;
			ansId=i;
		}
	}
	printf("%d\n%d\n",ans,ansId);
	return 0;
}

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct car {
	long long x,y;
};

bool cmp (const car &a, const car &b) {
	if (a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

int main () {
	int n,t;
	scanf("%d%d",&n,&t);
	vector<car> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%I64d%I64d",&tbl[i].x,&tbl[i].y);
		tbl[i].y*=t;
		tbl[i].y+=tbl[i].x;
	}
	sort(tbl.begin(),tbl.end(),cmp);
	vector<car> xx;
	xx.push_back(tbl[0]);
	for (int i=1;i<n;i++) {
		if (tbl[i].x==xx.back().x&&tbl[i].y==xx.back().y) xx.push_back(tbl[i]);
		else if (tbl[i].x==xx.back().x) xx.back().y=tbl[i].y;
		else {
			xx.push_back(tbl[i]);
		}
	}

	int cnt=0;
	long long cur=-1;
	for (int i=0;i<(int)xx.size();i++) {
		//printf("%I64d\n",xx[i].y);
		if (xx[i].y>cur) {
			cnt++;
			cur=xx[i].y;
		}
	}
	printf("%d\n",cnt);
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct pole{
	int x,y,mp;
};

bool cmp (const pole &a, const pole &b) {
	return a.y<b.y;
}

bool cmp2 (const pole &a, const pole &b) {
	return a.x<b.x;
}

deque<int> q;
int mrk[600100];

int main () {
	int n,h,l;
	scanf("%d%d%d",&n,&h,&l);
	vector<pole> tbl;
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		for (int j=0;j<=l&&b-j>=0;j++) {
			tbl.push_back(pole{a,b-j,0});
		}
	}
	sort(tbl.begin(),tbl.end(),cmp);
	int last=-1;
	int cur=-1;
	for (int i=0;i<(int)tbl.size();i++) {
		if (tbl[i].y!=last) {
			cur++;
			tbl[i].mp=cur;
			last=tbl[i].y;
		} else {
			tbl[i].mp=cur;
		}
	}
	sort(tbl.begin(),tbl.end(),cmp2);
	int xnow;
	int ans=-1;
	for (int i=0;i<(int)tbl.size();) {
		xnow=tbl[i].x;
		while (!q.empty()&&tbl[q.front()].x<xnow-h) {
			mrk[tbl[q.front()].mp]--;
			q.pop_front();
		}
		for (;i<(int)tbl.size()&&tbl[i].x==xnow;i++) {
			q.push_back(i);
			ans=max(ans,++mrk[tbl[i].mp]);
		}
	}
	printf("%d\n",ans);
	return 0;
}

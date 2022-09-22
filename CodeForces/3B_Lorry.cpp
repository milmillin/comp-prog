#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct boat{
	int a,b,i;
};

bool cmp (const boat &a, const boat &b) {
	if (a.b*b.a==b.b*a.a) return a.a>b.a;
	return a.b*b.a>b.b*a.a;
}

int main () {
	int n,v;
	scanf("%d%d",&n,&v);
	vector<boat> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].a,&tbl[i].b);
		tbl[i].i=i+1;
	}	
	sort(tbl.begin(),tbl.end(),cmp);
	
	int cnt=0;
	int cur=0;
	int lCur=-1;
	int llCur=-1;
	vector<int> ans[3];
	while (v&&cur<n) {
		if (v>=tbl[cur].a) {
			v-=tbl[cur].a;
			cnt+=tbl[cur].b;
			ans[tbl[cur].a].push_back(tbl[cur].i);
			if (tbl[cur].a==2) lCur=cur;
			if (tbl[cur].a==1) llCur=cur;
		}
		cur++;
	}

	lCur++;
	
	if (v==1&&lCur<n&&ans[1].size()) {
		while (lCur<n) {
			if (tbl[lCur].a==1) continue;
			if (tbl[lCur].b>tbl[llCur].b) {
				cnt-=tbl[llCur].b;
				cnt+=tbl[lCur].b;
				ans[1].pop_back();
				ans[tbl[lCur].a].push_back(tbl[lCur].i);
				break;
			}
			lCur++;
		}
	}

	printf("%d\n",cnt);
	for (int i=0;i<(int)ans[1].size();i++) {
		printf("%d ",ans[1][i]);
	}
	for (int i=0;i<(int)ans[2].size();i++) {
		printf("%d ",ans[2][i]);
	}
	printf("\n");
	return 0;
}

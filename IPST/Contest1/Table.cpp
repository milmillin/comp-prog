#include <cstdio>
#include <queue>

using namespace std;

int cntRow[400];
int timeRow[400];
int addRow[400];
int timee[400][5010];
int tbl[400][5010];

struct ei {
	int val,r,c,timee;
};

bool operator< (const ei &a, const ei &b) {
	if (a.val==b.val) return a.timee>b.timee;
	return a.val>b.val;
}

priority_queue<ei> q;

int main () {
	int r,c,m;
	scanf("%d%d%d",&r,&c,&m);
	int k,a,b,d;
	for (int i=1;i<=r;i++) {
		q.push(ei{0,i,-1,0});
	}
	for (int i=1;i<=m;i++) {
		scanf("%d",&k);
		if (k==1) {
			scanf("%d%d%d",&a,&b,&d);
			tbl[a][b]=d;
			if (timee[a][b]<=timeRow[a]) cntRow[a]++;
			timee[a][b]=i;
			q.push(ei{d,a,b,i});
		} else if (k==2) {
			scanf("%d%d",&a,&b);
			addRow[a]=b;
			timeRow[a]=i;
			cntRow[a]=0;
			q.push(ei{b,a,-1,i});
		} else if (k==3) {
			scanf("%d%d",&a,&b);
			if (timee[a][b]<timeRow[a]) printf("%d\n",addRow[a]);
			else printf("%d\n",tbl[a][b]);
		} else if (k==4) {
			int val,rr,cc,ti;
			while (!q.empty()) {
				val=q.top().val;
				rr=q.top().r;
				cc=q.top().c;
				ti=q.top().timee;
				//q.pop();
				//printf("--%d %d %d %d\n",val,rr,cc,ti);
				if (cc==-1) {
					if (ti==timeRow[rr]&&cntRow[rr]<c) {
						printf("%d\n",val);
						break;
					} else {
						q.pop();
						continue;
					}
				} else {
					if (ti==timee[rr][cc]&&ti>timeRow[rr]) {
						printf("%d\n",val);
						break;
					} else {
						q.pop();
						continue;
					}
				}
			}
		}
	}
	return 0;
}

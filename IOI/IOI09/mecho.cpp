#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct cell {
	int r,c;
};

queue<cell> bee;
queue<cell> bear;
bool wall[1010][1010];

int disBear[1010][1010];
int disBee[1010][1010];
cell home;
cell start;

int di[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int n,s;

bool check(int x) {
	memset(disBear,63,sizeof(disBear));
	disBear[start.r][start.c]=x*s;
	if (disBee[start.r][start.c]<=x) return false;
	bear.push(start);
	int nowr,nowc,nextr,nextc;
	while (!bear.empty()) {
		nowr=bear.front().r;
		nowc=bear.front().c;
		bear.pop();
		for (int i=0;i<4;i++) {
			nextr=nowr+di[i][0];
			nextc=nowc+di[i][1];
			if (nextc<0||nextc>=n||nextr<0||nextr>=n) continue;
			if (wall[nextr][nextc]) continue;
			if (disBear[nextr][nextc]<=disBear[nowr][nowc]+1) continue;
			if (disBee[nextr][nextc]<=(disBear[nowr][nowc]+1)/s) continue;
			disBear[nextr][nextc]=disBear[nowr][nowc]+1;
			bear.push(cell{nextr,nextc});
		}
	}

	return disBear[home.r][home.c]!=0x3f3f3f3f;
}

int main () {
	scanf("%d%d",&n,&s);
	char x;
	

	memset(disBee,63,sizeof(disBee));
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			scanf(" %c",&x);
			if (x=='T') wall[i][j]=true;
			else if (x=='M'){
				start=cell{i,j};
			}
			else if (x=='D') home=cell{i,j};
			else if (x=='H') {
				bee.push(cell{i,j});
				disBee[i][j]=0;
			}
		}
	}


	int nowr,nowc;
	int nextr,nextc;
	while (!bee.empty()) {
		nowr=bee.front().r;
		nowc=bee.front().c;
		bee.pop();
		for (int i=0;i<4;i++) {
			nextr=nowr+di[i][0];
			nextc=nowc+di[i][1];
			if (nextc<0||nextc>=n||nextr<0||nextr>=n) continue;
			if (wall[nextr][nextc]) continue;
			if (nextr==home.r&&nextc==home.c) continue;
			if (disBee[nextr][nextc]<=disBee[nowr][nowc]+1) continue;
			disBee[nextr][nextc]=disBee[nowr][nowc]+1;
			bee.push(cell{nextr,nextc});
		}
	}

	int lo=0;
	int hi=n*n;
	int mid;	
	while (lo<hi) {
		mid=(lo+hi+1)>>1;
		if (check(mid)) {
			lo=mid;
		} else {
			hi=mid-1;
		}
	}

	if (check(lo)) printf("%d\n",lo);
	else printf("-1\n");

	return 0;
}

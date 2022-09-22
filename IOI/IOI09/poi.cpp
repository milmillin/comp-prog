#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int solve[2010][2010];
int scr[2010];

struct p {
	int score,numsolve,id;
};

bool operator< (const p &a, const p &b) {
	if (a.score!=b.score) return a.score>b.score;
	if (a.numsolve!=b.numsolve) return a.numsolve>b.numsolve;
	return a.id<b.id;
}

p tbl[2010];

int main () {
	int n,t,pp;
	scanf("%d%d%d",&n,&t,&pp);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=t;j++) {
			scanf("%d",&solve[i][j]);
			if (!solve[i][j]) scr[j]++;
		}
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=t;j++) {
			tbl[i].score+=solve[i][j]*scr[j];
			tbl[i].numsolve+=solve[i][j];
		}
		tbl[i].id=i;
	}	
	sort(tbl+1,tbl+n+1);
	for (int i=1;i<=n;i++) {
		if (tbl[i].id==pp) {
			printf("%d %d\n",tbl[i].score,i);
		}
	}
	return 0;
}

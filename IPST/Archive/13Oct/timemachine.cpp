#include<cstdio>
#include <algorithm>

using namespace std;

int x[20];
int y[20];
int timee[20];
bool visit[20];

int n,m,k;
int minn;

int getDis(int f,int t) {
	return ceil(sqrt((x[f]-x[t])*(x[f]-x[t])+(y[f]-y[t])*(y[f]-y[t])));
}

void recur(int idx,int dis) {
	minn=min(minn,dis-timee[idx]+getDis(idx,k+1));
	visit[idx]=true;
	for (int i=1;i<=k;i++) {
		if (visit[i]) continue;
		recur(i,dis-timee[idx]+getDis(idx,i));
	}
	visit[idx]=false;
}

int main () {

	scanf("%d%d%d",&n,&m,&k);
	x[0]=y[0]=0;
	for (int i=1;i<=k;i++) {
		scanf("%d%d%d",&x[i],&y[i],&timee[i]);
	}
	x[k+1]=n-1;
	y[k+1]=m-1;
	//minn=getDis(0,k);
	minn=2e9;
	recur(0,0);
	printf("%d\n",minn);
	return 0;
}

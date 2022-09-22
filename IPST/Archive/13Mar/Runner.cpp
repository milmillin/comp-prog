#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int tbl[200][5010];

int get(int i,int j) {
	if (j<0) return tbl[i][0];
	if (j>5000) return tbl[i][5000];
	return tbl[i][j];
}

int divF(int a,int b) {
	return a/b;
}

int divC(int a,int b) {
	int tmp=a/b;
	if (a-tmp*b) return tmp+1;
	return tmp;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int t,v;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&t,&v);
		tbl[v][t]++;
	}
	for (int i=1;i<=100;i++) {
		for (int j=1;j<5010;j++) {
			tbl[i][j]+=tbl[i][j-1];
		}
	}
	int y,x1,x2;
	
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&y,&x1,&x2);
		int ans=0;
		for (int j=1;j<=100;j++) {
			//ans+=tbl[j][max(min((int)floor((x2*j-y)/j),5001),0)]-tbl[j][min(max((int)ceil((x1*j-y)/j)-1,0),5001)];
			ans+=get(j,x2-divC(y,j))-get(j,x1-(y/j)-1);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}

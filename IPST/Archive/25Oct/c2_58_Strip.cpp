#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[30][100100];

void update(int i,int j,int val) {
	tbl[i-j+10][min(i,j)]+=val;
}

int get(int i,int j) {
	return tbl[i-j+10][min(i,j)];
}

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int a,b,c,d;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int rgt=a-min(a+10,d);
		int bot=min(b+10,c)-b;	
		for (int i=max(a-10,b);i<=min(a+10,d);i++) {
			//x1
			update(a,i,1);
		}
		for (int i=max(b-10,a+1);i<=min(b+10,c);i++) {
			//y1
			update(i,b,1);
		}	
		c++;
		d++;
		//printf("%d %d\n",rgt,bot);
		for (int i=max(c-bot,b);i<=min(c-rgt,d);i++) {
			//x2
			update(c,i,-1);
		}
		for (int i=max(d+rgt,a);i<=min(d+bot,c-1);i++) {
			//y2
			update(i,d,-1);
		}
	}
	int cur;
	for (int i=0;i<=20;i++) {
		cur=0;
		for (int j=0;j<100100;j++) {
			cur+=tbl[i][j];
			tbl[i][j]=cur;
		}
	}
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		printf("%d\n",get(a,b));
	}
}

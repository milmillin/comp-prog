#include <cstdio>

using namespace std;

int up[100100];
int down[100100];
int hgt[100100];

void update(int* tbl,int idx,int val) {
	while (idx<100100) {
		tbl[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int* tbl,int idx) {
	int sum=0;
	while (idx) {
		sum+=tbl[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (a==1) {
			if (get(hgt,b)==get(hgt,b-1)) update(up,b,1);
			if (get(hgt,c)==get(hgt,c+1)) update(down,c+1,1);
			update(hgt,b,1);
			update(hgt,c+1,-1);
			if (get(hgt,b)==get(hgt,b-1)) update(down,b,-1);
			if (get(hgt,c)==get(hgt,c+1)) update(up,c+1,-1);
		} else if (a==2) {
			printf("%d %d\n",get(hgt,b),get(hgt,c));
		} else if (a==3) {
			printf("%d %d %d %d\n",get(hgt,b),get(hgt,c),get(up,c)-get(up,b),get(down,c)-get(down,b));
		}
		//for (int i=1;i<=n;i++) {
			//printf("%d ",get(hgt,i));
		//}
		//printf("\n");
	}
	return 0;
}

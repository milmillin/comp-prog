#include <cstdio>

using namespace std;

int bit[2000][2000];

void update(int r,int c,int val) {
	for (int i=r;i<2000;i+=(i&-i)) {
		for (int j=c;j<2000;j+=(j&-j)) {
			bit[i][j]+=val;
		}
	}
}

int get(int r,int c) {
	int sum=0;
	for (int i=r;i>0;i-=(i&-i)) {
		for (int j=c;j>0;j-=(j&-j)) {
			sum+=bit[i][j];
		}
	}	
	return sum;
}

int main () {
	while (true) {
		int cmd,a,b,c,d;
		scanf("%d",&cmd);
		if (cmd==0) {
			scanf("%d",&a);
		} else if (cmd==1) {
			scanf("%d%d%d",&a,&b,&c);
			a++;
			b++;
			update(a,b,c);
		} else if (cmd==2) {
			scanf("%d%d%d%d",&a,&b,&c,&d);
			a++;
			b++;
			c++;
			d++;
			printf("%d\n",get(c,d)-get(a-1,d)-get(c,b-1)+get(a-1,b-1));
		} else if (cmd==3) break;

	}
	return 0;
}

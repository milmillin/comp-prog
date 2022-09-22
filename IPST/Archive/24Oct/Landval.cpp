#include <cstdio>

using namespace std;

int bit[200100];

void update(int idx,int val) {
	while (idx<200100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c,d;
	for (int i=0;i<m;i++) {
		scanf("%d",&a);
		if (a==1) {
			scanf("%d%d%d",&b,&c,&d);
			update(b,d);
			update(c+1,-d);
		} else {
			scanf("%d",&b);
			printf("%d\n",get(b));
		}
	}
}

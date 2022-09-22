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
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (a==1) {
			update(c,b);
		} else {
			printf("%d\n",get(c)-get(b-1));
		}
	}
	return 0;
}

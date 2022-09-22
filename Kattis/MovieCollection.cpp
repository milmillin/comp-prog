#include <cstring>
#include <cstdio>

using namespace std;

int bit[200100];
int pos[100100];

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void update(int idx,int val) {
	while (idx<200100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

void f() {
	memset(bit,0,sizeof(bit));
	memset(pos,0,sizeof(pos));
	//printf("yay\n");
	int m,n;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		pos[i]=100001+i;
		//printf("%d\n",pos[i]);
		update(100001+i,1);
	}
	int cur=100001;
	int x;
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		printf("%d ",get(pos[x])-1);
		update(pos[x],-1);
		update(cur,1);
		pos[x]=cur;
		cur--;
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

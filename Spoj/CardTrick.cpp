#include <cstdio>
#include <cstring>

using namespace std;

int bit[20010];

void update(int idx,int val) {
	while (idx<20010) {
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

int fnd(int idx) {
	int lo=1;
	int hi=20010;
	int mid;
	while (lo<hi) {
		mid=(lo+hi)/2;
		if (get(mid)<idx) {
			lo=mid+1;
		} else {
			hi=mid;
		}
	}
	return hi;
}

int ans[20010];

void f() {
	int n;
	scanf("%d",&n);
	if (n==1) {
		printf("1\n");
		return;
	}
	memset(bit,0,sizeof(bit));
	for (int i=1;i<=n;i++) {
		update(i,1);
	}
	ans[2]=1;
	update(2,-1);
	int cur=2;
	int mod=n-1;
	int tmp;
	for (int i=2;i<=n;i++) {
		cur=(cur-1+i)%mod+1;
		mod--;
		//printf("%d\n",cur);
		tmp=fnd(cur);
		ans[tmp]=i;
		update(tmp,-1)
	}
	for (int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

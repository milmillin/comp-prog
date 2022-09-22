#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];
int mp[100100];
int bit[100100];

void set(int idx,int val) {
	while (idx<100100) {
		bit[idx]=max(bit[idx],val);
		idx+=(idx&-idx);
	}
}

int get(int idx) {
	int sum=0;
	while (idx) {
		sum=max(sum,bit[idx]);
		idx-=(idx&-idx);
	}
	return sum;
}

int tmp[20];

int main () {
	freopen("nocross.in","r",stdin);
	freopen("nocross.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	int x;
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		mp[x]=i;
	}
	
	for (int i=1;i<=n;i++) {
		for (int j=-4;j<=4;j++) {
			if (tbl[i]+j<1) continue;
			if (tbl[i]+j>n) continue;
			tmp[j+5]=get(mp[tbl[i]+j])+1;
			//set(mp[tbl[i]+j]+1,get(mp[tbl[i]+j])+1);
		}
		for (int j=-4;j<=4;j++) {
			if (tbl[i]+j<1) continue;
			if (tbl[i]+j>n) continue;
			set(mp[tbl[i]+j]+1,tmp[j+5]);
		}
	}
	printf("%d\n",get(n+1));
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mp[100100];
int mp2[100100];
int tbl[100100];
int tbl2[100100];

int b1[100100];
//int b2[100100];

void add(int *bit, int idx,int val) {
	while (idx<100100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int *bit,int idx) {
	int sum =0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int main() {
	freopen("mincross.in","r",stdin);
	freopen("mincross.out","w",stdout);
	int n;
	scanf("%d",&n);
	int x;
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		mp[x]=i;
		tbl2[i]=x;
	}
	
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		tbl[i]=mp[x];
		mp2[x]=i;
	}
	
	long long cur=0;
	for (int i=n;i>=1;i--) {
		cur+=get(b1,tbl[i]-1);
		add(b1,tbl[i],1);
		//add(b2,100100-tbl[i],1);
	}
	long long ans=cur;
	for (int i=n;i>=1;i--) {
		cur-=n-tbl[i];
		cur+=tbl[i]-1;
		ans=min(ans,cur);
	}

	cur=0;
	memset(b1,0,sizeof(b1));
	for (int i=n;i>=1;i--) {
		cur+=get(b1,mp2[tbl2[i]]-1);
		add(b1,mp2[tbl2[i]],1);
	}
	ans=min(ans,cur);
	for (int i=n;i>=1;i--) {
		cur-=n-mp2[tbl2[i]];
		cur+=mp2[tbl2[i]]-1;
		ans=min(ans,cur);
	}
	

	printf("%lld\n",ans);
	return 0;
}

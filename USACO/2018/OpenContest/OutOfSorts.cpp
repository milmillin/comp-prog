#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];
int id[100100];

bool cmp(int a,int b) {
	if (tbl[a]==tbl[b]) return a<b;
	return tbl[a]<tbl[b];
}

int num[100100];

int main () {
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		id[i]=i;
	}
	sort(id,id+n,cmp);
	int mx=0;
	for (int i=1;i<n;i++) {
		mx=max(mx,id[i-1]);
		num[i]=mx-i+1;
	}
	long long ans=0;
	for (int i=0;i<n;i++) {
		int cur=0;
		if (i) cur=max(cur,num[i]);
		if (i<n-1) cur=max(cur,num[i+1]);
		if (cur==0&&n>1) cur++;
		ans+=cur;
	}
	printf("%lld\n",ans);
	return 0;
}

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;


int tbl[100100];

int ask(int l,int r,int sz,long long sum) {
	int cnt=1;
	int cur=0;
	long long cursum=0;
	//printf("%d %d\n",l,r);
	for (int i=l;i<r;i++) {
		cur++;
		cursum+=tbl[i];	
		if (tbl[i]>sum) return 1e9;
		if (cur>sz||cursum>sum) {
			cur=1;
			cursum=tbl[i];
			cnt++;
			//if (i==r-1) cnt--;
		}
	}
	//printf("\n");
	return cnt;
}

int n,m,k;
int solve(int mid,int mypart) {
	if (mid-mypart+1<=0) return 1e9;
	if (mid+1>=n) return 1e9;
	int lo=0;
	int hi=1e9;
	//printf("%d %d\n",mid-mypart+1,mid+1);
	while (lo<hi) {
		int md=(lo+hi)>>1;
		//printf("%d\n",mid);
		int tmp=ask(0,mid-mypart+1,m,md);
		int tmp2=ask(mid+1,n,m,md);
		//printf("%d %d %d\n",md,tmp,tmp2);
	
		if (tmp+tmp2<k) {
			hi=md;
		} else {
			lo=md+1;
		}
	}	
	return hi;
}

int main () {
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int mypart=min(m,n-k+1);
	//printf("%d\n",mypart);
	long long sum=0;
	for (int i=0;i<mypart;i++) {
		sum+=tbl[i];
	}
	//printf("%lld\n",sum);
	long long mx=sum;
	int mid=mypart-1;
	for (int i=mypart;i<n;i++) {
		sum+=tbl[i];
		sum-=tbl[i-mypart];
		if (sum>mx) {
			mx=sum;
			mid=i;
		}	
	}
	//int lo=0;
	//int hi=1e9;
	////printf("%d %d\n",mid-mypart+1,mid+1);
	//while (lo<hi) {
		//int md=(lo+hi)>>1;
		////printf("%d\n",mid);
		//int tmp=ask(0,mid-mypart+1,m,md);
		//int tmp2=ask(mid+1,n,m,md);
		////printf("%d %d %d\n",md,tmp,tmp2);
	
		//if (tmp+tmp2<k) {
			//hi=md;
		//} else {
			//lo=md+1;
		//}
	//}	
	//assert(hi!=1e9);
	printf("%d\n",min(solve(mid,mypart),min(solve(mid+1,mypart),solve(mid-1,mypart))));
	//printf("%lld %d\n",mx,mid);
	//for (int i=mid-mypart+1;i<n-mypart;i++) {
		//tbl[i]=tbl[i+mypart];
	//}
	//n-=mypart;
	//for (int i=0;i<n;i++) {
		//printf("%d ",tbl[i]);
	//}
	//printf("\n");
	return 0;
}

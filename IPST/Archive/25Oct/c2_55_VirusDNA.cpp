#include <cstdio>
#include <algorithm>

using namespace std;

//int seg[3000000];
//int ll[3000000];
//int rr[3000000];
//int idAtSeg[1000100];
int bit[1000100];
int bit2[1000100];

void update(int idx,int val) {
//	if (idx<0) return;
	while (idx<1000100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int idx) {
	//if (idx<0) return 0;
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void update2(int idx,int val) {
	//if (idx<0) return;
	while (idx<1000100) {
		bit2[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get2(int idx) {
	//if (idx<0) return 0;
	int sum=0;
	while(idx) {
		sum+=bit2[idx];
		idx-=(idx&-idx);
	}
	return sum;
}
/*
void init(int idx,int l,int r) {
	ll[idx]=l;
	rr[idx]=r;
	if (l==r) {
		seg[idx]=2e9;
		idAtSeg[l]=idx;
		return;
	}
	init(idx*2+1,l,(l+r)/2);
	init(idx*2+2,(l+r)/2+1,r);
	seg[idx]=min(seg[idx*2+1],seg[idx*2+2]);
}

void upp(int idx,int l,int r,int val) {
	if (l>rr[idx]||r<ll[idx]) return;
	if (l<=ll[idx]&&r>=rr[idx]) seg[idx]=min(seg[idx],val);
	else {
		upp(idx*2+1,l,r,val);
		upp(idx*2+2,l,r,val);
		seg[idx]=min(seg[idx*2+1],seg[idx*2+2]);
	}
}

int gett(int idx,int l,int r) {
	if (l>rr[idx]||r<ll[idx]) return 2e9;
	if (l<=ll[idx]&&r>=rr[idx]) return seg[idx];
	else return min(gett(idx*2+1,l,r),gett(idx*2+2,l,r));	
}
*/

int findd(int val) {
	int lo=1;
	int hi=1000000;
	while (lo<hi) {
		int mid=(lo+hi)/2;
		//printf("%d\n",mid);
		if (get(mid)<val) lo=mid+1;
		else hi=mid;
	}
	return hi;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	char x;
	int a,b;
	for (int i=1;i<=n;i++) {
		update(i,1);
		//chg[i]=2e9;
	}
	//init(0,1,n);	
	//for (int j=1;j<=n;j++) {
		//printf("%d ",seg[idAtSeg[j]]);
	//}
	//printf("\n");
	//int timee=1;
	for (int i=0;i<m;i++) {
		//printf("%d\n",i);
		scanf(" %c",&x);
		if (x=='d') {
			scanf("%d",&a);
			a++;
			int tmp=findd(a);
			if (get(tmp)==a) {
				update(tmp,-1);
				int dif=get2(tmp)-get2(tmp-1);
				update2(tmp,-dif+1);
				tmp=findd(get(tmp));
				update2(tmp,dif);
			} else {
				update(tmp,-1);
				update2(tmp,1);
			}
		} else if (x=='g') {
			scanf("%d",&a);
			a++;
			int tmp=findd(a+1);
			update(tmp,1);
			int tmp2=findd(get(tmp-1));
			update2(tmp2,1);
			//timee++;
		} else if (x=='i') {
			scanf("%d%d",&a,&b);
			if (a<=0) a=1;
			printf("%d\n",get2(b-1)-get2(a-1));
		}
		//for (int j=1;j<=n;j++) {
			//printf("%d ",get(j));
		//}
		//printf("\n");
		//for (int j=1;j<=n;j++) {
			//printf("%d ",get2(j));
		//}
		//printf("\n");
	}
	return 0;
}

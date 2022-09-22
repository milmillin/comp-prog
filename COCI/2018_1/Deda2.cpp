#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int seg[600100];

void update(int idx,int l,int r,int k,int val) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		seg[idx]=val;
		return;
	}
	int m = (l+r)>>1;
	update(idx*2,l,m,k,val);
	update(idx*2+1,m,r,k,val);
	seg[idx]=min(seg[idx*2],seg[idx*2+1]);
	//printf("++ %d %d %d\n",l,r,seg[idx]);
}

int get(int idx,int l,int r,int ll,int rr,int k) {
	//printf("gg %d %d %d %d %d %d\n",l,r,ll,rr,k,seg[idx]);
	if (ll>=r||rr<=l) return 2e9;
	if (l+1==r) return (seg[idx]<=k)?l:2e9;
	if (ll<=l&&rr>=r&&seg[idx]>k) return 2e9;
	int m = (l+r)>>1;
	if (ll>=m) {
		return get(idx*2+1,m,r,ll,rr,k);
	} else if (rr<=m) {
		return get(idx*2,l,m,ll,rr,k);
	} else {
		int tmp = get(idx*2,l,m,ll,rr,k);
		if (tmp!=2e9) return tmp;
		return get(idx*2+1,m,r,ll,rr,k);
		//return min(get(idx*2,l,m,ll,rr,k),get(idx*2+1,m,r,ll,rr,k));
		//if (seg[idx*2]<=k) return get(idx*2,l,m,ll,rr,k);
		//else if (seg[idx*2+1]<=k) return get(idx*2+1,m,r,ll,rr,k);
		//else return 2e9;
	}
}

int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	memset(seg,63,sizeof(seg));
	char x;
	int a,b;
	for (int i=0;i<q;i++) {
		scanf(" %c%d%d",&x,&a,&b);
		if (x=='M') {
			update(1,1,n+1,b,a);
		} else {
			int tmp = get(1,1,n+1,b,n+1,a);
			printf("%d\n",(tmp==2e9)?-1:tmp);
		}
	}
	
	return 0;
}

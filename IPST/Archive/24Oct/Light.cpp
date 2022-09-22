#include <cstdio>
#include <algorithm>

using namespace std;

int ll[400100];
int rr[400100];
int blue[400100];
int red[400100];
int tbl[400100];
bool flag[400100];

int init(int idx,int l,int r){
	//printf("%d %d %d\n",idx,l,r);
	ll[idx]=l;
	rr[idx]=r;
	if (l==r) {
		return blue[idx]=tbl[l];
	}
	return blue[idx] = init(idx*2+1,l,(l+r)/2) + init(idx*2+2,(l+r)/2+1,r);
}

void get(int idx,int l,int r) {
	if (!flag[idx]) return;
	flag[idx]=false;
	swap(blue[idx],red[idx]);
	//if (l!=r) {
		flag[idx*2+1]^=1;
		flag[idx*2+2]^=1;
	//}
}

void update(int idx,int l,int r) {
	if (l>rr[idx]||r<ll[idx]) return;
	//printf("call %d %d %d\n",idx,l,r);
	if (l<=ll[idx]&&r>=rr[idx]) {
		if (flag[idx]) {
			flag[idx]=false;
			return;
		}
		swap(blue[idx],red[idx]);
		//if (l!=r) {
		flag[idx*2+1]^=1;
		flag[idx*2+2]^=1;
		//}
		return;
	}
	if (flag[idx]) {
		flag[idx]=false;
		flag[idx*2+1]^=1;
		flag[idx*2+2]^=1;
	}
	if (l>=ll[idx*2+2]) {
		//all at right
		get(idx*2+1,ll[idx*2+1],rr[idx*2+1]);
		update(idx*2+2,l,r);
		
	} else if (r<=rr[idx*2+1]) {
		//all at left
		update(idx*2+1,l,r);
		get(idx*2+2,ll[idx*2+2],rr[idx*2+2]);
	} else {
		update(idx*2+1,l,rr[idx*2+1]);
		update(idx*2+2,ll[idx*2+2],r);
	}
	blue[idx]=blue[idx*2+1]+blue[idx*2+2];
	red[idx]=red[idx*2+1]+red[idx*2+2];
}

struct ei {
	int val,idx;
};

bool operator< (const ei &a, const ei &b) {
	return a.val<b.val;
}

ei mir[100100];
int id[100100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<k;i++) {
		scanf("%d",&mir[i].val);
		mir[i].idx=i;
	}
	sort(mir,mir+k);
	for (int i=0;i<k;i++) {
		id[mir[i].idx]=i;
		if (i) {
			tbl[i]=mir[i].val-mir[i-1].val;
		} else {
			tbl[i]=mir[i].val;
		}
	}
	tbl[k]=n-mir[k-1].val;
	//for (int i=0;i<=k;i++) {
		//printf("%d ",tbl[i]);
	//}
	//printf("\n");
	init(0,0,k);
	//for (int i=0;i<2*k+2;i++) {
		//printf("%d,%d ",blue[i],red[i]);
	//}
	//printf("\n");
	for (int i=0;i<k;i++) {
		
		update(0,id[i]+1,k);
		printf("%d\n",blue[0]);
		//for (int i=0;i<2*k+2;i++) {
			//printf("%d,%d ",blue[i],red[i]);
		//}
		//printf("\n");
	}
	return 0;
}

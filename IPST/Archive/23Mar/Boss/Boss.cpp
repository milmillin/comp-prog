#include <vector>
#include <cstdio>

using namespace std;

vector<int> pth[100100];

int par[100100];
int ii[100100];
int oo[100100];

int cur=1;

void recur(int idx) {
	ii[idx]=cur;
	cur++;
	for (int i=0;i<(int)pth[idx].size();i++) {
		recur(pth[idx][i]);
	}
	oo[idx]=cur;
}

int seg[500100];
int flag[500100];
int fgId[500100];
int last[500100];

int query(int idx,int l, int r,int k) {
	//printf("%d %d %d %d\n",idx,l,r,k);
	if (flag[idx]) {
		if (seg[idx]==fgId[idx]) {
			flag[idx*2]=flag[idx*2+1]=flag[idx];
			fgId[idx*2]=fgId[idx*2+1]=fgId[idx];
			seg[idx]=flag[idx];
		}
		flag[idx]=fgId[idx]=0;
	}
	if (l+1==r) return seg[idx];
	int m=(l+r)>>1;
	if (k<m) return query(2*idx,l,m,k);
	else return query(2*idx+1,m,r,k);
}

void update(int idx,int l,int r,int ll,int rr,int val,int rem) {
	//printf("%d %d %d %d %d %d %d\n",idx,l,r,ll,rr,val,rem);
	if (flag[idx]) {
		if (seg[idx]==fgId[idx]) {
			flag[idx*2]=flag[idx*2+1]=flag[idx];
			fgId[idx*2]=fgId[idx*2+1]=fgId[idx];
			seg[idx]=flag[idx];
		}
		flag[idx]=fgId[idx]=0;
	}
	if (ll>=r) return;
	if (rr<=l) return;
	if (ll<=l&&rr>=r) {
		if (seg[idx]==rem) {
			seg[idx]=val;
			flag[idx*2]=flag[idx*2+1]=val;
			fgId[idx*2]=fgId[idx*2+1]=rem;
		}
		return;
	}
	int m=(l+r)>>1;
	update(idx*2,l,m,ll,rr,val,rem);
	update(idx*2+1,m,r,ll,rr,val,rem);
}

void printTree(int idx,int l,int r) {
	printf("%d %d %d %d %d\n",idx,l,r,seg[idx],flag[idx]);
	if (l+1==r) return;
	int m=(l+r)>>1;
	printTree(idx*2,l,m);
	printTree(idx*2+1,m,r);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		pth[x].push_back(i);
		par[i]=x;
	}
	recur(1);
	for (int i=1;i<=n;i++) {
		printf("%d %d\n",ii[i],oo[i]);
	}
	seg[1]=1;
	flag[2]=1;
	flag[3]=1;
	fgId[2]=0;
	fgId[3]=0;
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		//printTree(1,1,oo[1]);
		//printf("**\n");
		if (a==1) {
			//add b
			update(1,1,oo[1],ii[b],oo[b],b,query(1,1,oo[1],ii[b]));
		} else if (a==2) {
			//remove b
			update(1,1,oo[1],ii[b],oo[b],query(1,1,oo[1],ii[par[b]]),b);
		} else {
			//ask b
			printf("%d\n",query(1,1,oo[1],ii[b]));
		}
		//printTree(1,1,oo[1]);
		//printf("--\n");
		//for (int j=1;j<=n;j++) {
			//printf("%d ",query(1,1,oo[1],ii[j]));
		//}
		//printf("\n");
	}
	
	return 0;
}

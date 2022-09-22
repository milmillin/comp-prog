#include <cstdio>
#include <algorithm>

using namespace std;

int minn[300100];
int maxx[300100];
int ll[300100];
int rr[300100];
int id[100100];
int tbl[100100];

void init(int idx,int l,int r) {
	ll[idx]=l;
	rr[idx]=r;
	maxx[idx]=r;
	minn[idx]=l;
	if (l==r) {
		id[l]=idx;
		return;
	}
	init(idx*2+1,l,(l+r)/2);
	init(idx*2+2,(l+r)/2+1,r);
}

int getMax(int idx,int l,int r) {
	if (r<ll[idx]||l>rr[idx]) return 0;
	if (l<=ll[idx]&&r>=rr[idx]) return maxx[idx];
	else return max(getMax(idx*2+1,l,r),getMax(idx*2+2,l,r));
}

int getMin(int idx,int l,int r) {
	if (r<ll[idx]||l>rr[idx]) return 2e9;
	if (l<=ll[idx]&&r>=rr[idx]) return minn[idx];
	else return min(getMin(idx*2+1,l,r),getMin(idx*2+2,l,r));
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	init(0,0,n-1);
	for (int i=0;i<n;i++) {
		tbl[i]=i;
	}
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (a==0) {
			//swap
			swap(tbl[b],tbl[c]);
			maxx[id[b]]=minn[id[b]]=tbl[b];
			maxx[id[c]]=minn[id[c]]=tbl[c];
			int cur=(id[b]-1)/2;
			while (true) {
				minn[cur]=min(minn[cur*2+1],minn[cur*2+2]);
				maxx[cur]=max(maxx[cur*2+1],maxx[cur*2+2]);
				if (cur==0) break;
				cur=(cur-1)/2;
			}
			cur=(id[c]-1)/2;
			while (true) {
				minn[cur]=min(minn[cur*2+1],minn[cur*2+2]);
				maxx[cur]=max(maxx[cur*2+1],maxx[cur*2+2]);
				if (cur==0) break;
				cur=(cur-1)/2;
			}
		} else {
			printf("%s\n",(getMax(0,b,c)==c&&getMin(0,b,c)==b)?"YES":"NO");
		}
	}
	return 0;
}

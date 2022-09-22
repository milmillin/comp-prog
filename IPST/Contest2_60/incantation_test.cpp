#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<long long>> mat;

int c[200];
int f;

mat mul(const mat &a,const mat &b) {
	mat tmp=mat(f,vector<long long>(f,0));
	
	for (int i=0;i<f;i++) {
		for (int j=0;j<f;j++) {
			for (int k=0;k<f;k++) {
				tmp[i][j]=max(tmp[i][j],a[i][k]+b[k][j]);
			}
		}
	}

	return mat(tmp);
}

mat exp(const mat &a, int b) {
	if (b==1) return mat(a);
	mat tmp=mul(a,a);
	if (b%2) return mul(tmp,a);
	return mat(tmp);
}

int d[200];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	int e=1<<k;
	int mxx=0;
	for (int i=0;i<e;i++) {
		scanf("%d",&c[i]);
		mxx=max(mxx,c[i]);
	}
	f=e>>1;
	mat a=vector<vector<long long>>(f,vector<long long>(f,0));		

	int mask=f-1;

	for (int i=0;i<e;i++) {
		d[mask&i]=max(d[mask&i],c[i]);
	}

	int msk=e>>2;
	msk-=1;
	//printf("-- %d\n",mask);

	for (int i=0;i<f;i++) {
		for (int j=0;j<f;j++) {
			if ((j&msk)==((i&(msk<<1))>>1)) {
				a[i][j]=c[(j<<1)|i];
			}
			printf("%lld ",a[i][j]);
		}
		printf("\n");
	}


	if (n<k) {
		printf("0\n");
		return 0;
	} else if (n==k) {
		printf("%d\n",mxx);
		return 0;	
	}

	mat res=exp(a,n-k);
	
	long long ans=0;
	for (int i=0;i<f;i++) {
		long long cur=0;
		for (int j=0;j<f;j++) {
			cur=max(cur,res[i][j]+d[j]);
		}
		ans=max(cur,ans);
	}
	printf("%lld\n",ans);
	
	return 0;
}

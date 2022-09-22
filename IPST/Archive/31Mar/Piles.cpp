#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int fact[200];

void init() {
	fact[0]=1;
	fact[1]=1;
	for (int i=2;i<200;i++) {
		fact[i]=fact[i-1]*i;
		fact[i]%=9871;
	}
}

int ext(int a,int b,int &x,int &y) {
	if (a==0) {
		x=0;
		y=1;
		return b;
	}
	int x1,y1;
	int g=ext(b%a,a,x1,y1);
	x=y1-(b/a)*x1;
	y=x1;
	return g;
}

int inv(int a,int m) {
	int x,y;
	ext(a,m,x,y);
	return (x%m+m)%m;
}

int k;
int mic[200][200][200];

int dfs(int rmd,int pile,int cnt) {
	if (rmd<0) return 0;
	//printf("%d %d %d %d\n",rmd,pile,cnt,res);
	if (rmd==0) {
		//ans+=inv(res,9871);
		//ans%=9871;
		return 1;
	}
	if (mic[rmd][pile][cnt]!=-1) return mic[rmd][pile][cnt];
	int ans=0;
	for (int i=min(pile,rmd);i>=k;i--) {
		//dfs(rmd-i,i,(i==pile)?cnt+1:1,(res*fact[i]*((i==pile)?cnt+1:1))%9871);
		ans+=inv((fact[i]*((i==pile)?cnt+1:1)),9871)*dfs(rmd-i,i,(i==pile)?cnt+1:1);
		ans%=9871;
	}
	return mic[rmd][pile][cnt]=ans;
}

void f() {
	int n;
	scanf("%d%d",&n,&k);
	memset(mic,-1,sizeof(mic));
	printf("%d\n",(fact[n]*dfs(n,n,0))%9871);
}

int main () {
	init();
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

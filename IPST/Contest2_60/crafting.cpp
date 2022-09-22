#include <cstdio>
#include <algorithm>

using namespace std;

int c[30];
bool broken;

long long ei(int n,int w) {
	if (n==1) {
		if (w<=0) broken=true;
		return w;
	}
	int tmp=w*2+1;
	tmp-=c[n-1];
	long long ans=0;
	ans+=ei(n-1,tmp/2);
	ans+=ei(n-1,tmp/2+tmp%2);
	return ans;
}


int main () {
	int n,w;
	scanf("%d%d",&n,&w);
	for (int i=1;i<n;i++) {
		scanf("%d",&c[i]);
	}
	long long ans=ei(n,w);
	printf("%lld\n",(broken)?-1:ans);
	return 0;
}

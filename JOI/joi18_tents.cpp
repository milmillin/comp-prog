#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int mod = 1000000007;

long long mic[3010][3010];

long long mul(long long a,long long b) {
	return (a*b)%mod;
}

long long add(long long a,long long b) {
	return ((a+b)%mod+mod)%mod;
}

long long add(long long a,long long b,long long c) {
	return add(add(a,b),c);
}

long long dp(int a,int b) {
	if (mic[a][b]!=-1) return mic[a][b];	
	if (a<0||b<0) return 0;
	if (a==0||b==0) return 1;
	if (a==1) return add(mul(b,4),b*(b-1)/2);	
	if (b==1) return add(mul(a,4),a*(a-1)/2);
	
	long long res=0;
	//res=add(res,add(dp(a-1,b),dp(a,b-1),-dp(a-1,b-1)));

	res=add(res,mul(dp(a-2,b-1),a*(a-1)/2));
	
	//res=add(res,mul(dp(a-1,b-3),(b-1)*(b-2)/2));
	//res=add(res,mul(dp(a-1,b-2),(b-1)));

	//res=add(res,mul(dp(a-1,b-1),a*4));
	//res=add(res,mul(dp(a-1,b-2),(b-1)*4));

	res=add(res,mul(dp(a-1,b-2),b*(b-1)/2));
	res=add(res,mul(dp(a-1,b-1),a+b-1)*5);

	res=add(res,-mul(dp(a-2,b-2),(a-1)*(b-1)*16));
	res=add(res,-mul(dp(a-3,b-3),(long long)(a-1)*(a-2)*(b-2)*(b-1)/4));
	res=add(res,-mul(dp(a-2,b-3),(long long)(b-1)*(b-2)*(a-1)*2));
	res=add(res,-mul(dp(a-3,b-2),(long long)(b-1)*(a-1)*(a-2)*2));
	//res=add(res,4);
	
	return mic[a][b]=res;
}

int main () {
	int a,b;
	scanf("%d%d",&a,&b);
	memset(mic,-1,sizeof(mic));
	printf("%lld\n",dp(a,b));
	return 0;
}

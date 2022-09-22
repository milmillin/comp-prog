#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int x[100100];
int y[100100];

map<int,int> mx;
map<int,int> my;

int cx[100100];
int cy[100100];

int mod=1e9+7;

long long poww(int x,int b) {
	if (b==0) return 1;
	if (b==1) return x;
	long long tmp=poww(x,b/2);
	tmp=(tmp*tmp)%mod;
	if (b%2) return (tmp*x)%mod;
	return tmp;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x[i],&y[i]);
		mx[x[i]];
		my[y[i]];
	}
	int curx=0;
	for (auto &i:mx) {
		i.second=curx++;
	}
	int cury=0;
	for (auto &i:my) {
		i.second=cury++;
	}
	for (int i=0;i<n;i++) {
		cx[mx[x[i]]]++;
		cy[my[y[i]]]++;
	}

	long long xx=poww(2,curx);
	long long yy=poww(2,cury);
	printf("%lld\n",(xx*yy)%mod);

	long long ans1=1,ans2=0;
	long long now1,now2;
	for (int i=0;i<curx;i++) {
		now1=(ans1+ans2)%mod;
		now2=(ans1+ans2)%mod;
		now2*=poww(2,cx[i]);
		now2%=mod;
		now2+=mod-1;
		now2%=mod;
		ans1=now1;
		ans2=now2;
	}
	long long ansx=(ans1+ans2)%mod;
	ans1=1;
	ans2=0;
	for (int i=0;i<cury;i++) {
		now1=(ans1+ans2)%mod;
		now2=now1;
		now2*=poww(2,cy[i]);
		now2%=mod;
		now2+=mod-1;
		now2%=mod;
		ans1=now1;
		ans2=now2;
	}
	long long ansy=(ans1+ans2)%mod;
	long long ans=ansx*ansy;
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}

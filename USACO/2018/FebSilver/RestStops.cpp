#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

int x[100100];
int tbl[100100];
int mx[100100];



int main () {
	freopen("reststops.in","r",stdin);
	freopen("reststops.out","w",stdout);
	int l,n,rf,rb;
	scanf("%d%d%d%d",&l,&n,&rf,&rb);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x[i],&tbl[i]);
	}
	for (int i=n-1;i>=0;i--) {
		mx[i]=max(tbl[i],mx[i+1]);
	}
	long long ans=0;
	int last=0;
	int dif = rf-rb;
	for (int i=0;i<n;i++) {
		if (tbl[i]==mx[i]) {
			ans+=(long long)tbl[i]*dif*(x[i]-last);	
			last=x[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}

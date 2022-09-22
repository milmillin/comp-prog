#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);	
	vector<long long> stk(n+2,1e18);
	stk[0]=0;
	int mx=1;
	long long x;
	for (int i=0;i<n;i++) {
		scanf("%lld",&x);
		auto tmp=upper_bound(stk.begin(),stk.end(),x*6);
		mx=max(mx,(int)(tmp-stk.begin()));

		for (auto it=tmp;it!=stk.begin();it--) {
			*(it)=min(*(it),*(it-1)+x);
		}
		//auto left=tmp-1;
		//long long xx=(tmp==stk.begin())?0:*left;
		//*tmp=min(*tmp,xx+x);
		//for (auto j:stk) {
			//printf("%lld ",j==1e18?-1:j);
		//}
		//printf("\n");
	}
	printf("%d\n",mx);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}

	return 0;
}

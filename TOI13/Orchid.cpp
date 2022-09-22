#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int>stk(n,2e9);
	int x;
	int mx=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		auto aa = upper_bound(stk.begin(),stk.end(),x);
		mx=max(mx,(int)(aa-stk.begin()));
		//pintf("%d\n",aa-stk.begin());
		//if (aa!=stk.begin()) *(aa-1)=x;
		*aa=x;
	}
	//printf("%d\n",mx);
	printf("%d\n",n-mx-1);
	return 0;
}

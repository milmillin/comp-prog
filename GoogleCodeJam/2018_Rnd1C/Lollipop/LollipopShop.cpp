#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	vector<int> count(n,0);
	vector<bool> sold(n,false);
	int d;
	int cur,x;
	int mncnt;
	for (int i=0;i<n;i++) {
		scanf("%d",&d);
		cur=-1;
		mncnt=2e9;
		for (int j=0;j<d;j++) {
			scanf("%d",&x);
			count[x]++;
			if (sold[x]) continue;
			if (count[x]<mncnt) {
				mncnt=count[x];
				cur=x;
			}
		}	
		printf("%d\n",cur);
		fflush(stdout);
		if (cur!=-1) sold[cur]=true;
	}	
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		//printf("Case #%d: ",i);
		f();
	}
	return 0;
}

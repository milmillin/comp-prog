#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int x[100100];
int y[100100];
int t[100100];

int main () {
	freopen("slingshot.in","r",stdin);
	freopen("slingshot.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&x[i],&y[i],&t[i]);
	}
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		int ans=abs(a-b);
		for (int j=0;j<n;j++) {
			ans=min(ans,abs(a-x[j])+abs(y[j]-b)+t[j]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

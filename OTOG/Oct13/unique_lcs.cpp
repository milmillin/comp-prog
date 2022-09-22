#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int cnt[300100];
int pos[300100];
int stk[300100];

void f() {
	memset(cnt,0,sizeof(cnt));
	memset(pos,0,sizeof(pos));
	memset(stk,63,sizeof(pos));
	int n,l1,l2;
	scanf("%d%d%d",&n,&l1,&l2);
	int x;
	for (int i=0;i<l1;i++) {
		scanf("%d",&x);
		cnt[x]++;
		pos[x]=i+1;
	}
	int mx=0;
	for (int i=0;i<l2;i++) {
		scanf("%d",&x);
		cnt[x]++;
		if (cnt[x]==2) {
			auto it=upper_bound(stk,stk+300100,pos[x]);
			*it=pos[x];
			mx=max(mx,(int)(it-stk+1));
		}
	}
	//printf("\n");
	printf("%d\n",mx);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}

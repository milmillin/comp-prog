#include <cstdio>

using namespace std;

int last[256];
char tbl[1000100];
bool st[256];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf(" %c",&tbl[i]);
		last[tbl[i]]=i;
	}
	int cnt=0;
	for (int i=0;i<n;i++) {
		if (!st[tbl[i]]) {
			st[tbl[i]]=true;
			cnt++;
		}
		if (cnt>k) {
			printf("YES\n");
			return 0;
		}
		if (last[tbl[i]]==i) {
			cnt--;
			st[tbl[i]]=false;
		}
	}
	printf("NO\n");
	return 0;
}

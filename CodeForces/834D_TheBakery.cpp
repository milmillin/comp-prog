#include <cstdio>

using namespace std;

int tbl[40000];
int last[40000];
bool st[40000];
int dp[40000];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		last[tbl[i]]=i;
	}
	
	for (int i=0;i<n;i++) {
		
	}

	return 0;
}

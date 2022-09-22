#include <cstdio>

using namespace std;

int s[100100];
int dis[100100];
int mic[100100][2];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&s[i]);
		if (i) dis[i]=s[i]-s[i-1];
	}
	return 0;
}

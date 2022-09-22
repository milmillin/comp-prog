#include <cstdio>

using namespace std;

int hgt[1000];

int s[1000];
int d[1000];

int main () {
	int n,b;
	scanf("%d%d",&n,&b);
	for (int i=0;i<n;i++) {
		scanf("%d",&hgt[i]);
	}
	for (int i=0;i<b;i++) {
		scanf("%d%d",&s[i],&d[i]);
	}
	int curBoot=0;
	int cur=0;
	while (cur<n-1) {
		if (s[curBoot]<hgt[cur]) {
			curBoot++;
			continue;
		}
		for (int i=0;i<n;i++)
	}
	return 0;
}

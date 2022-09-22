#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	int win,unix,mac;
	win=unix=mac=1;
	int last=0;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (x==13) mac++;
		else if (x==10) {
			unix++;
			if (last==13) win++;
		}
		last=x;
	}
	printf("%d %d %d\n",win,unix,mac);
	return 0;
}

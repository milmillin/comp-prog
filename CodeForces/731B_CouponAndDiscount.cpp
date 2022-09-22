#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	bool lastDay=false;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (lastDay) {
			if (!x) {
				printf("NO\n");
				return 0;
			}
			lastDay=false;
			x--;
		}
		if (x%2) {
			lastDay=true;
		} else {
			if (lastDay) {
				printf("NO\n");
				return 0;
			}
		}
	}
	if (lastDay) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	return 0;
}

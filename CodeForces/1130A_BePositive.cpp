#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d", &n);
	int cntp = 0;
	int cntn = 0;
	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x > 0) cntp++;
		if (x < 0) cntn++;

	}
	if (cntp >= (n + 1) / 2) {
		printf("1\n");
	} else if (cntn >= (n + 1) / 2) {
		printf("-1\n");
	} else {
		printf("0\n");
	}

	
	return 0;
}

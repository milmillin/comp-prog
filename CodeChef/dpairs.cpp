#include <cstdio>
#include <algorithm>

using namespace std;

int a[200100];
int b[200100];

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	int mna = 2e9;
	int mnaid = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (a[i] < mna) {
			mna = a[i];
			mnaid = i;
		}
	}
	int mxb = -2e9;
	int mxbid = -1;
	for (int i = 0; i < m; i++) {
		scanf("%d", &b[i]);
		if (b[i] > mxb) {
			mxb = b[i];
			mxbid = i;
		}
	}
	for (int i = 0; i < m; i++) {
		printf("%d %d\n", mnaid, i);
	}
	for (int i = 0; i < n; i++) {
		if (i == mnaid) continue;
		printf("%d %d\n", i, mxbid);
	}
}

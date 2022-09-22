#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

//int a[1100000];
//long long f[1048576][21];

long long f[1048576];

int main() {
	int n;
	scanf("%d", &n);
	int sz = 1 << n;
	for (int i = 0; i < sz; i++) {
		scanf("%lld", &f[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < sz; mask++) {
			if (mask & (1 << i)) {
				f[mask] += f[mask ^ (1 << i)];
			}
		}
	}

	/*
	for (int i = 0; i < sz; i++) {
		int fix = 0;
		int cur = i;
		while (cur) {
			int lastBit = cur & -cur;
			f[i][fix] = f[i ^ lastBit][fix];
			cur -= lastBit;
			fix++;
		}
		f[i][fix] = a[i];
		for (int j = fix - 1; j >= 0; j--) {
			f[i][j] += f[i][j + 1];
		}
	}
	*/

	for (int i = 0; i < sz; i++) {
		//long long f = 0;
		//for (int j = 0; j <= i; j++) {
			//if ((j & i) == j) {
				//f += a[j];
			//}
		//}
		//printf("%I64d ", f);
		printf("%lld ", f[i]);
	}
	printf("\n");
	return 0;
}

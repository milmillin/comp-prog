#include <cstdio>

using namespace std;

int tbl[300000][300];

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &tbl[0][i]);
	}
	bool dif = false;
	for (int j = 1; j <= n; j++) {
		if (tbl[0][j] != tbl[0][tbl[0][j]]) dif = true;
	}
	if (!dif) {
		printf("1\n");
		return 0;
	}
	int i = 1;
	while (dif) {
		dif = false;
		for (int j = 1; j <= n; j++) {
			tbl[i][j] = tbl[0][tbl[i-1][j]];
		}
		for (int j = 1; j <= n; j++) {
			if (tbl[i][j] != tbl[i][tbl[i][j]]) dif = true;
		}
		//printf("\n");
		if (!dif) {
			printf("%d\n", i+1);
			return 0;
		}
		i++;
	}
	return 0;
}

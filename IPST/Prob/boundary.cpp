#include <cstdio>
#include <algorithm>

using namespace std;

int e[1010][100];
int f[1010][100];

int dis[50][1010][1010];

int main () {
	int r, c;
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		for (int j = 1; j <= c - 1; j++) {
			scanf("%d", &e[i][j]);
		}
	}
	for (int j = 0; j < c; j++) {
		for (int i = 1; i <= r - 1; i++) {
			scanf("%d", &f[i][j]);
		}
	}
	for (int i = 1; i <= r - 1; i++) {
		for (int j = 0; j < c; j++) {
			f[i][j] += f[i - 1][j];
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			dis[0][i][j] = abs(f[j][0] - f[i][0]);
		}
	}
	for (int k = 1; k < c; k++) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < r; j++) {
				
			}
		}
	}
	return 0;
}

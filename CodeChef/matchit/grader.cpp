#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct point {
	int x, y;

	bool operator<(const point &r) const {
		if (x != r.x) return x < r.x;
		return y < r.y;
	}
};

int n, m;
bool orgPts[1010][1010];
long long tbl[1010][1010];
bool visit[1010][1010];

bool readinput(char* filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) return false;
	fscanf(f, "%d%d", &n, &m);
	int x, y;
	for (int i = 0; i < 2 * m; i++) {
		fscanf(f, "%d%d", &x, &y);
		orgPts[x][y] = true;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			fscanf(f, "%lld", &tbl[i][j]);
		}
	}
	fclose(f);
	return true;
}

bool checkAdj(int x1, int y1, int x2, int y2) {
	if (x1 == x2) {
		if (y1 == y2 - 1 || y1 == y2 + 1) return true;
	}
	if (y1 == y2) {
		if (x1 == x2 - 1 || x1 == x2 + 1) return true;
	}
	return false;
}

long long sum = 0;

int readoutput(FILE *f) {
	for (int i = 0; i < m; i++) {
		int len;
		if (!fscanf(f, "%d", &len)) return -1;
		int x, y;
		int lx, ly;
		for (int j = 0; j < len; j++) {
			fscanf(f, "%d%d", &x, &y);
			if (visit[x][y]) return -2;
			visit[x][y] = true;
			sum += tbl[x][y];
			if (j == 0 || j == len - 1) {
				if (!orgPts[x][y]) return -3;
				orgPts[x][y] = false;
			}
			if (j) {
				if (!checkAdj(lx, ly, x, y)) return -4;
			}
			lx = x;
			ly = y;
		}
	}
	return 1;
}

int main (int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: grader.exe inputfile outputfile\n");
		return -1;
	}
	if (!readinput(argv[1])) {
		fprintf(stderr, "error: cannot read inputfile\n");
		return -1;
	}
	FILE *f = fopen(argv[2], "r");
	if (f == NULL) {
		fprintf(stderr, "error: cannot read outputfile\n");
		return -1;
	}
	int res = readoutput(f);
	fclose(f);
	if (res < 0) {
		printf("Wrong Answer (%d)\n", res);
		return -1;
	}

	long long total = (long long)n * n * 1e9;

	printf("Accepted\n");
	printf("  sum = %lld\n", sum);
	printf("  total = %lld\n", total);
	printf("  score = %lf\n", pow((double)sum/total + 1, 6));
	return 0;
}

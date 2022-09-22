#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> tpls = {{2, 3, 3, 2},
							{1, 1, 4, 4},
							{3, 2, 2, 3},
							{4, 4, 1, 1}};

vector<vector<int>> tpl2r = {{2, 2, 3, 1, 1, 3},
							{1, 1, 3, 2, 2, 3}};

vector<vector<int>> tpl2c = {{2, 1},
								{2, 1},
								{3, 3},
								{1, 2},
								{1, 2},
								{3, 3}};

vector<vector<int>> tpl1r = {{1, 1, 2, 2}};
vector<vector<int>> tpl1c = {{1},
								{1},
								{2},
								{2}};

int ans[60][60];
bool usedSame[4];
bool usedDiff[4];

void apply(int r, int c, vector<vector<int>> &tpl, int sr, int sc) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			ans[i][j] = tpl[i % sr][j % sc];
			if ((i % 2) == (j % 2)) {
				usedSame[ans[i][j]] = true;
			} else {
				usedDiff[ans[i][j]] = true;
			}
		}
	}
}

void f() {
	int r, c;
	scanf("%d%d", &r, &c);
	memset(usedSame, 0, sizeof(usedSame));
	memset(usedDiff, 0, sizeof(usedDiff));
	if (r == 1) {
		apply(r, c, tpl1r, 1, 4);
	} else if (c == 1) {
		apply(r, c, tpl1c, 4, 1);
	} else if (r == 2) {
		apply(r, c, tpl2r, 2, 6);
	} else if (c == 2) {
		apply(r, c, tpl2c, 6, 2);
	} else {
		apply(r, c, tpls, 4, 4);
	}
	int cntSame = 0;
	int cntDiff = 0;
	for (int i = 0; i < 4; i++) {
		if (usedSame[i]) cntSame++;
		if (usedDiff[i]) cntDiff++;
	}
	printf("%d\n", max(cntSame, cntDiff));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}

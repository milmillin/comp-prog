#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

bool iswater[60][60];
int di[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
bool visit[60][60];

vector<pair<int, int>> source;
queue<pair<int, int>> q;

int main () {
	char x;
	int n;
	scanf("%d", &n);
	int r1, c1;
	int r2, c2;
	scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf(" %c", &x);
			if (x == '0') iswater[i][j] = false;
			else iswater[i][j] = true;
		}
	}
	visit[r1][c1] = true;
	q.push({r1, c1});
	int nowr, nowc, nextr, nextc;
	while (!q.empty()) {
		nowr = q.front().first;
		nowc = q.front().second;
		q.pop();
		source.push_back({nowr, nowc});
		for (int i = 0; i < 4; i++) {
			nextr = nowr + di[i][0];
			nextc = nowc + di[i][1];
			if (nextr <= 0 || nextc <= 0 || nextr > n || nextc > n) continue;
			if (iswater[nextr][nextc]) continue;
			if (visit[nextr][nextc]) continue;
			visit[nextr][nextc] = true;
			q.push({nextr, nextc});
		}
	}

	int maxdis = 1e9;

	visit[r2][c2] = true;
	q.push({r2, c2});
	while (!q.empty()) {
		nowr = q.front().first;
		nowc = q.front().second;
		q.pop();
		for (auto& cell : source) {
			maxdis = min(maxdis, (nowr - cell.first) * 
					(nowr - cell.first) + (nowc - cell.second) *
					(nowc - cell.second));
		}
		for (int i = 0; i < 4; i++) {
			nextr = nowr + di[i][0];
			nextc = nowc + di[i][1];
			if (nextr <= 0 || nextc <= 0 || nextr > n || nextc > n) continue;
			if (iswater[nextr][nextc]) continue;
			if (visit[nextr][nextc]) continue;
			visit[nextr][nextc] = true;
			q.push({nextr, nextc});
		}
	}
	printf("%d\n", maxdis);
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

char s[1000010];

vector<int> idx[26];
int mem[510][510];
char q[510];

int solve(int i, int j) {
	if (j == 0) return 0;
	if (i == 0) return 1e9;
	if (mem[i][j] != -1) return mem[i][j];
	int a = solve(i-1,j-1);
	vector<int> &aa = idx[q[i] - 'a'];
	auto newi = upper_bound(aa.begin(), aa.end(), a);	
	int nn = (newi == aa.end())?1e9 : *newi;
	
	return mem[i][j] = min(solve(i - 1, j), nn);
}

int main () {	
	int n, qq;
	scanf("%d%d", &n, &qq);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) {
		idx[s[i] - 'a'].push_back(i);
	}	
	for (int i = 0; i < qq; i++) {
		scanf("%s", q + 1);
		memset(mem, -1, sizeof(mem));
		int qn = strlen(q + 1);
		//printf("%d\n", solve(qn, 2));
		for (int i = qn; i >= 0; i--) {
			//printf("%d %d\n", i, solve(qn, i));
			if (solve(qn, i) <= n) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}

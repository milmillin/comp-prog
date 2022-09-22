#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class Solver {
	int n, m;
	string x;
	vector<string> pat;
	vector<vector<int>> matches;
	vector<bool> visit;
	vector<vector<int>> next_matches;
	vector<vector<int>> prev_matches;
	long long ans;

	vector<int> prefixFunction(const string &pat) {
		vector<int> lsp(pat.size());
		lsp[0] = 0;
		for (int i = 1; i < (int)pat.size(); i++) {
			int j = lsp[i - 1];
			while (j > 0 && pat[i] != pat[j]) {
				j = lsp[j - 1];
			}
			if (pat[i] == pat[j]) {
				j++;
			}
			lsp[i] = j;
		}
		return lsp;
	}

	vector<int> findMatches(const string &str, const string &pat) {
		vector<int> matches;
		vector<int> lsp = prefixFunction(pat);

		int j = 0;
		for (int i = 0; i < (int)str.size(); i++) {
			while (j > 0 && str[i] != pat[j]) {
				j = lsp[j - 1];
			}
			if (str[i] == pat[j]) {
				j++;
				if (j == (int)pat.size()) {
					matches.push_back(i - j + 1);
					j = lsp[j - 1];
				}
			}
		}
		return matches;
	}

	void processInput() {
		for (int i = 0; i < m; i++) {
			cin >> pat[i];
			matches[i] = findMatches(x, pat[i]);
			for (auto j : matches[i]) {
				next_matches[i][j] = prev_matches[i][j] = j;
			}
			for (int j = n - 2; j >= 0; j--) {
				next_matches[i][j] = min(next_matches[i][j], next_matches[i][j + 1]);
			}
			for (int j = 1; j < n; j++) {
				prev_matches[i][j] = max(prev_matches[i][j - 1], prev_matches[i][j]);
			}
		}
		
	}

	void solve() {
		vector<int> left;
		vector<int> right;
		for (int i = 0; i < m; i++) {
			if (visit[i]) left.push_back(i);
			else right.push_back(i);
		}
		vector<int> way(n + 1, 0);

		//solve left
		do {
			int bound = 0;
			for (auto i : left) {
				if (bound >= n) {
					bound = n + 1;
					break;
				}
				bound = next_matches[i][bound] + (int)pat[i].size();
			}
			if (bound - 1 < n) way[bound - 1]++;
		} while (next_permutation(left.begin(), left.end()));

		//quick sum
		int cur = 0;
		for (int i = 0; i < (int)way.size(); i++) {
			cur += way[i];
			way[i] = cur;
		}

		//solve right
		do {
			int bound = n - 1;
			for (int j = right.size() - 1; j >= 0; j--) {
				int i = right[j];
				if (bound - (int)pat[i].size() + 1 < 0) {
					bound = -2;
					break;
				}
				bound = prev_matches[i][bound - (int)pat[i].size() + 1] - 1;
			}
			if (bound >= 0) {
				ans += way[bound];
			}
		} while (next_permutation(right.begin(), right.end()));
	}

	void dfs(int id, int dep, int target) {
		visit[id] = true;
		if (dep == target) {
			solve();
		} else {
			for (int i = id + 1; i < m; i++) {
				dfs(i, dep + 1, target);
			}
		}
		visit[id] = false;
	}

	public:
	Solver(int _n, int _m): n(_n), m(_m), pat(m), matches(m), visit(m, false),
			next_matches(m, vector<int>(n, n)), prev_matches(m, vector<int>(n, -2)), ans(0ll) {
		cin >> x;
		processInput();
		for (int i = 0; i < m; i++) {
			dfs(i, 1, (m + 1) / 2);
		}
		printf("%lld\n", ans);
	}
};

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	Solver solver(n, m);
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int lo[1000100];
int hi[1000100];

struct ei {
	int hgt, cnt;
};

bool operator< (const ei &a, const ei &b) {
	return a.hgt > b.hgt;
}

vector<ei> stk;
vector<int> qs;
int cur;

int main () {
	int n;
	scanf("%d", &n);

	cur = 0;
	stk.push_back(ei{(int)2e9, 0});
	qs.push_back(0);

	int ans = 0;
	int nc;

	int cc;

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &lo[i], &hi[i]);
		auto x = lower_bound(stk.begin()+cur, stk.end(), ei{hi[i],0});
		nc = x - stk.begin();

		//for (auto &j:stk) {
			//printf(" * * %d %d\n", j.hgt, j.cnt);
		//}
		//printf("-- %d %d %d\n\n", cur,nc, qs.back() - qs[nc - 1] + 1);

		ans = max(ans, qs.back() - qs[nc - 1] +1);

		cc = 1;
		while (!stk.empty() && stk.back().hgt < lo[i]) {
			if (stk.size()-1>=cur) cc += stk.back().cnt;
			stk.pop_back();
			qs.pop_back();
		}
		stk.push_back(ei{lo[i], cc});
		qs.push_back(cc + qs.back());

		cur = min((int)stk.size() - 1, nc);

		
	}
	
	printf("%d\n", ans);
	return 0;
}

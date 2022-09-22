#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1000000007;

class Solution {

	struct num {
		int val;
		bool inf;
		
		num(int _val): val(_val), inf(false) {}
		num(bool _inf): val(0), inf(true) {}
		num(int _val, bool _inf): val(_val), inf(_inf) {}
		num(): num(0) {}

		num operator+ (const num &r) const {
			return num((val + r.val) % mod, inf || r.inf);
		}

		void adjust() {
			if (val == 0) inf = false;
		}
	};

	vector<int> val;
	vector<vector<int>> pth;

	vector<int> dis;
	vector<int> lo;

	vector<bool> inStk;
	vector<int> stk;

	vector<vector<int>> cmp;
	vector<num> cmpVal;

	vector<int> cmpOf;
	vector<vector<int>> cmpPth;
	vector<int> cmpIndeg;

	int timee;

	void add(vector<int> &comp) {
		int sum = 0;
		for (auto i : comp) {
			sum += val[i];
			sum %= mod;
		}
		if ((int)comp.size() > 1) cmpVal.push_back(num(sum, true));
		else if (pth[comp[0]][0] == comp[0] || pth[comp[0]][1] == comp[1]) cmpVal.push_back(num(sum, true));
		else cmpVal.push_back(num(sum));
		int now = (int)cmp.size();
		for (auto i : comp) {
			cmpOf[i] = now;
		}
		cmp.push_back(comp);
	}

	void scc(int x) {
		dis[x] = lo[x] = timee++;
		stk.push_back(x);
		inStk[x] = true;

		for (auto i : pth[x]) {
			if (!dis[i]) {
				scc(i);
				lo[x] = min(lo[x], lo[i]);
			} else if (inStk[i]) {
				lo[x] = min(lo[x], dis[i]);
			}
		}
		
		//printf("%d %d %d\n", x, dis[x], lo[x]);
		//fflush(stdout);

		if (lo[x] == dis[x]) {
			vector<int> comp;
			while (stk.back() != x) {
				comp.push_back(stk.back());
				inStk[stk.back()] = false;
				stk.pop_back();
			}
			comp.push_back(stk.back());
			inStk[stk.back()] = false;
			stk.pop_back();
			add(comp);
		}
	}

	vector<num> mem;
	num propagate(int x) {
		if (mem[x].val != -1) return mem[x];
		num res = cmpVal[x];
		for (auto i : cmpPth[x]) {
			if (i == x) continue;
			num cur = propagate(i);
			res = res + cur;
		}
		res.adjust();
		return mem[x] = res;
	}

	public:
	Solution(int n): val(n), pth(n), dis(n), lo(n), inStk(n), cmpOf(n), timee(1), mem(n, num(-1)) {
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			a--;
			b--;
			pth[i].push_back(a);
			pth[i].push_back(b);
		}

		for (int i = 0; i < n; i++) {
			scanf("%d", &val[i]);
		}

		for (int i = 0; i < n; i++) {
			if (!dis[i]) scc(i);
		}

		//for (int i = 0; i < (int)cmp.size(); i++) {
			//printf("cmp %d: %d %d\n", i, cmpVal[i].val, cmpVal[i].inf);
		//}

		cmpPth.resize(cmp.size());
		cmpIndeg.resize(cmp.size(), 0);
		for (int i = 0; i < n; i++) {
			for (auto j : pth[i]) {
				cmpPth[cmpOf[j]].push_back(cmpOf[i]);
				//printf("cmpPth %d -> %d\n", cmpOf[j], cmpOf[i]);
			}
		}
		//for (auto &i : cmpPth) {
			//sort(i.begin(), i.end());
			//i.resize(unique(i.begin(), i.end()) - i.begin());
		//}

		num res = propagate(cmpOf[0]);
		//printf("--> %d %d\n", res.val, res.inf);

		if (res.inf) {
			printf("UNBOUNDED\n");
		} else {
			printf("%d\n", res.val);
		}
	}


};

int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		int n;
		scanf("%d", &n);
		Solution s(n);
		fflush(stdout);
	}
	return 0;
}

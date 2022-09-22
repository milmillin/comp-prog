#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <cstring>
#include <cstdarg>

using namespace std;

#ifdef debug
void log(const char *format, ...) {
	if (!debug) return;
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
#else
void log(const char *format, ...) {}
#endif

vector<int> pth[1000100];
vector<int> par[1000100];

int outdeg[1000100]; // number of child
int fulfill[1000100]; // number of removable child

// 0 - non-removable, 1 - removable, 3 - deleted
int type[1000100];
int promoted[1000100];
int minparoutdeg[1000100];

class comparator {
	public:
		bool operator() (int a, int b) {
			if (type[a] != type[b]) return type[a] < type[b];
			if ((promoted[a] != 0) != (promoted[b] != 0)) return promoted[b] != 0;
			return minparoutdeg[b] < minparoutdeg[a];
		}
};

priority_queue<int, vector<int>, comparator> q;
bool popped[1000100];

bool qEmpty() {
	while (!q.empty()) {
		if (popped[q.top()]) q.pop();
		else break;
	}
	return q.empty();
}

void promote(int idx) {
	log("promoting %d\n", idx);
	for (auto i: pth[idx]) {
		assert(type[i] != 0);
		promoted[i]++;
		minparoutdeg[i] = min(minparoutdeg[i], outdeg[idx]);
		q.push(i);
	}
}

vector<vector<int>> ans;

void remove(int idx) {
	log("removing %d\n", idx);
	type[idx] = 3;
	for (auto p: par[idx]) {
		outdeg[p]--;
		fulfill[p]--;
		if (outdeg[p] == 0) {
			type[p] = max(type[p], 1);
			q.push(p);
			
			for (auto pp: par[p]) {
				fulfill[pp]++;
				if (fulfill[pp] == outdeg[pp]) {
					//promote child of p
					promote(pp);
				}
			}
		}
	}
}

int main () {
	memset(minparoutdeg, 63, sizeof(minparoutdeg));
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		pth[a].push_back(b);
		par[b].push_back(a);
		outdeg[a]++;
	}

	for (int i = 1; i <= n; i++) {
		if (outdeg[i] == 0) {
			// i is now removable;
			log("%d is now removable\n", i);
			type[i] = 1;
			q.push(i);
			for (auto p: par[i]) {
				fulfill[p]++;
				if (fulfill[p] == outdeg[p]) {
					//promote child of p
					promote(p);
				}
			}
		}
	}

	while (!qEmpty()) {
		vector<int> current;
		current.push_back(q.top());
		popped[q.top()] = true;
		q.pop();
		if (!qEmpty()) {
			current.push_back(q.top());
			popped[q.top()] = true;
			q.pop();
		}
		ans.push_back(current);
		for (auto i: current) {
			remove(i);
		}
	}

	printf("%d\n", (int)ans.size());
	for (auto &ei: ans) {
		printf("%d ", (int)ei.size());
		for (auto &i: ei) {
			printf("%d ",i);
		}
		printf("\n");
	}
	return 0;
}

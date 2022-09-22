#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
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
int indeg[1000100];

int outdeg[1000100]; // number of child
int fulfill[1000100]; // number of removable child

// 0 - non-removable, 1 - removable,
// 2 - revealing-removable, 3 - deleted
int type[1000100];

queue<int> q1;
queue<int> q2;

bool q1Empty() {
	while (!q1.empty()) {
		if (type[q1.front()] != 1) q1.pop();
		else break;
	}
	return q1.empty();
}

bool q2Empty() {
	while (!q2.empty()) {
		if (type[q2.front()] != 2) q2.pop();
		else break;
	}
	return q2.empty();
}

void promote(int idx) {
	log("promoting %d\n", idx);
	for (auto i: pth[idx]) {
		assert(type[i] != 0);
		if (type[i] != 2) q2.push(i);
		type[i] = max(type[i], 2);
	}
}


vector<vector<int>> ans;

void remove(int idx) {
	log("removing %d\n", idx);
	bool is2 = type[idx] == 2;
	type[idx] = 3;
	for (auto p: par[idx]) {
		outdeg[p]--;
		fulfill[p]--;
		if (outdeg[p] == 0) {
			type[p] = max(type[p], 1);
			if (type[p] == 1) q1.push(p);
			
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
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		pth[a].push_back(b);
		par[b].push_back(a);
		outdeg[a]++;
		indeg[b]++;
	}

	for (int i = 1; i <= n; i++) {
		if (outdeg[i] == 0) {
			// i is now removable;
			log("%d is now removable\n", i);
			type[i] = 1;
			q1.push(i);
			for (auto p: par[i]) {
				fulfill[p]++;
				if (fulfill[p] == outdeg[p]) {
					//promote child of p
					promote(p);
				}
			}
		}
	}

	while (!q2Empty()) {
		vector<int> current;
		current.push_back(q2.front());
		q2.pop();
		if (!q2Empty()) {
			current.push_back(q2.front());
			q2.pop();
		} else if (!q1Empty()) {
			current.push_back(q1.front());
			q1.pop();
		}
		ans.push_back(current);
		for (auto i: current) {
			remove(i);
		}
	}
	while (!q1Empty()) {
		vector<int> current;
		current.push_back(q1.front());
		q1.pop();
		if (!q1Empty()) {
			current.push_back(q1.front());
			q1.pop();
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

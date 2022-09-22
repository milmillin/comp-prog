#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> undo;
vector<int> states;

bool isActive() {
	return undo.size()%2==0;
}

int main () {
	int n;
	scanf("%d", &n);
	states.push_back(0);
	int x;
	bool tmp;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x > 0) {
			if (!isActive()) states.pop_back();
			undo.clear();
			states.push_back(x);
		} else {
			//if (states.back() != 0) {
			x = -x;
			tmp = isActive();
			while (!undo.empty() && (undo.size()%2==tmp || undo.back() >= x)) undo.pop_back();
			if (!tmp&&undo.empty()&&states.size()>1) states.pop_back();
			if (states.back()!=0) undo.push_back(x);
			//}
		}
		printf("states: ");
		for (auto j : states) printf("%d ", j);
		printf("\n");
		printf("undo: ");
		for (auto j : undo) printf("%d ", j);
		printf("\n");
		printf("ans -- %d\n\n", (isActive())?states.back():states[states.size()-2]);
	}
	return 0;
}

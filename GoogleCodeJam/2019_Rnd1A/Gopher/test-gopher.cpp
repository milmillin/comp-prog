#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

vector<int> prime = {3,5,7,11,13,17,18};
set<vector<int>> ei;

int main () {
	for (int i = 1; i <= 1000000; i++) {
		vector<int> tmp;
		for (auto p : prime) {
			tmp.push_back(i % p);
		}
		assert(ei.find(tmp) == ei.end());
		ei.insert(tmp);
	}
	printf("yay %d\n", (int)ei.size());
	return 0;
}

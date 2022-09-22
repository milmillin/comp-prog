#include <cstdio>
#include <algorithm>

using namespace std;

vector<int> tbl;

pair<int,int> recur(bool turn) {
	if (tbl.size()<2) return make_pair(0,0);
	

}

int main() {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		tbl.push_back(x);
	}
	reverse(tbl.begin(),tbl.end());
	return 0;
}

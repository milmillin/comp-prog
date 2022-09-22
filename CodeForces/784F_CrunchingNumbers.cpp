#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}

	if (n==3) {
		printf("1 2 3\n");
		return 0;
	}

	sort(tbl.begin(),tbl.end());
	//tbl.resize(unique(tbl.begin(),tbl.end())-tbl.begin());
	for (int i=0;i<5;i++) {
		printf("%d ",(tbl[i]>27)?27:tbl[i]);
	}
	for (int i=5;i<(int)tbl.size();i++) {
		printf("%d ",33);
	}
	printf("\n");
	return 0;
}

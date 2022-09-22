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
	int cur=n-1;
	while (tbl[cur-1]>tbl[cur]) cur--;
	int swp=cur-1;
	cur=n-1;
	while (tbl[swp]>tbl[cur]) cur--;
	swap(tbl[swp],tbl[cur]);
	sort(tbl.begin()+swp+1,tbl.end());
	for (int i=0;i<n;i++) {
		printf("%d\n",tbl[i]);
	}

	return 0;
}

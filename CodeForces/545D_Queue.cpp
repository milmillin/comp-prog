#include <algorithm>
#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	sort(tbl.begin(),tbl.end());
	long long sum=0;
	int cnt=0;
	for (int i=0;i<n;i++) {
		if (tbl[i]>=sum) {
			sum+=tbl[i];
			cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}

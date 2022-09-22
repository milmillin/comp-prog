#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	vector<int> t0;
	vector<int> t1;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (i%2) t1.push_back(x);
		else t0.push_back(x);
	}
	sort(t0.begin(),t0.end());
	sort(t1.begin(),t1.end());
	vector<int> t;
	for (int i=0;i<(int)t0.size();i++) {
		t.push_back(t0[i]);
		if (i<(int)t1.size()) t.push_back(t1[i]);
	}
	for (int i=1;i<n;i++) {
		if (t[i]<t[i-1]) {
			printf("%d\n",i-1);
			return;
		}
	}
	printf("OK\n");
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}

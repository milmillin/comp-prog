#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

long long hh[100100];


vector < long long > stk;
vector < long long > qs;

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &hh[i]);
	}
	long long base = 0;
	int x;
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans = 0;
		scanf("%d", &x);
		hh[i] += base;
		stk.push_back(hh[i]);
		if (qs.empty()) qs.push_back(hh[i]);
		else qs.push_back(hh[i] + qs.back());


		ans += (long long)x * (stk.end() - upper_bound(stk.begin(), stk.end(), base + x));
		
		//printf("-- %d\n",(upper_bound(stk.begin(),stk.end(),base+x)-stk.begin()));

		int aa = upper_bound(stk.begin(), stk.end(), base) - stk.begin();
		int bb = upper_bound(stk.begin(), stk.end(), base + x) - stk.begin();
		//ans += qs[bb - 1] - qs[aa - 1];
		if (bb > 0) ans += qs[bb - 1];
		if (aa > 0) ans -= qs[aa - 1];
		ans -= base * (bb - aa);
		printf("%lld ", ans);
		base += x;
	}
	printf("\n");
	return 0;
}

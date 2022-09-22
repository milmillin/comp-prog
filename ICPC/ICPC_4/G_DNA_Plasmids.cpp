#include <algorithm>
#include <cstdio>
#include <deque>

using namespace std;

long long tbl[2000100];

deque<int> q;

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[i]);
		tbl[i+n]=tbl[i];
	}
	for (int i=1;i<2*n;i++) {
		tbl[i]+=tbl[i-1];
	}
	q.push_back(0);
	long long mx = max(0ll,tbl[0]);
	for (int i=1;i<2*n;i++) {
		while (!q.empty()&&q.front()<i-n) q.pop_front();
		mx=max(mx,tbl[i]-tbl[q.front()]);
		while (!q.empty()&&tbl[q.back()]>=tbl[i]) q.pop_back();
		q.push_back(i);
	}
	printf("%lld\n",mx);
	return 0;
}

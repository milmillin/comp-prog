#include <cstdio>
#include <queue>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	priority_queue<int,vector<int>,greater<int> >q;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		q.push(x);
	}
	int now=1;
	while (q.top()>=now) {
		q.push(q.top()+1);
		q.pop();
		now++;
	}
	printf("%d\n",now-1);
	return;
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct {
	int wgt,val;
} eiei;

bool operator< (const eiei &a, const eiei &b) {
	if (a.wgt==b.wgt) return a.val<b.val;
	return a.wgt>b.wgt;
}

priority_queue<eiei> q;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	char x;
	int a,b;
	for (int i=0;i<n+m;i++) {
		scanf(" %c",&x);
		if (x=='T') {
			scanf("%d%d",&a,&b);
			q.push(eiei{a,b});
		} else if (x=='P') {
			if (!q.empty()) {
				printf("%d\n",q.top().val);
				q.pop();
			} else {
				printf("0\n");
			}
		}
	}
	return 0;
}

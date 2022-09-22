#include <cstdio>
#include <queue>

using namespace std;

int tbl[100100];

typedef struct {
	int val, idx;
} edge;

bool operator< (const edge &a, const edge &b) {
	return a.idx>b.idx;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int del;
	int keep;
	int ans=0;
	int cur=0;
	priority_queue<edge> q;
	for (int i=1;i<n;i++) {
		del=i-1;
		keep=n-i;
		while (!q.empty()&&q.top().idx<i) {
			q.pop();
		}
		while (del) {
			int rm = min(q.top().val,del);
			edge a =q.top();
			a.val-=rm;
			del-=rm;
			if (!a.val) q.pop();
			else {
				q.pop();
				q.push(a);
			}
		}
		cur=0;
		if (!q.empty()&&q.top().idx==i) {
			cur+=q.top().val;
			q.pop();
		}
		cur+=keep;
		ans+=cur;
		//printf("%d\n",cur);
		q.push(edge{cur,tbl[i]});
	}
	printf("%d\n",ans);
	return 0;
}

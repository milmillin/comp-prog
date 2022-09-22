#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct st {
	int lev;
	int id;
	int left,rgt;
	int sl,sr;
};

bool operator< (const st &a, const st &b) {
	if (a.lev!=b.lev) return a.lev>b.lev;
	if (min(a.sl,a.sr)!=min(b.sl,b.sr)) return min(a.sl,a.sr)<min(b.sl,b.sr);
	if (max(a.sl,a.sr)!=max(b.sl,b.sr)) return max(a.sl,a.sr)<max(b.sl,b.sr);
	return a.id>b.id;
}

void f() {
	int n,k;
	scanf("%d%d",&n,&k);
	priority_queue<st> q;
	q.push(st{1,(n+1)/2,0,n+1,(n+1)/2-1,n-(n+1)/2});
	st now;
	int cnt=0;
	while (!q.empty()) {
		now = q.top();
		q.pop();
		//printf("%d %d %d %d %d %d\n",now.lev,now.id,now.left,now.rgt,now.sl,now.sr);
		cnt++;
		if (cnt==k) break;
		if (now.sl==0&&now.sr==0) continue;
		q.push(st{now.lev+1,(now.left+now.id)/2,now.left,now.id,(now.left+now.id)/2-now.left-1,now.id-(now.left+now.id)/2-1});
		q.push(st{now.lev+1,(now.id+now.rgt)/2,now.id,now.rgt,(now.id+now.rgt)/2-now.id-1,now.rgt-(now.id+now.rgt)/2-1});
	}
	printf("%d %d\n",max(now.sl,now.sr),min(now.sl,now.sr));
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

#include <cstdio>
#include <queue>

using namespace std;

typedef struct {
	int wgt,val,dur;
} thing;

bool operator< (const thing &a, const thing &b) {
	return a.wgt>b.wgt;
}

typedef struct {
	int day;
	int wgt,val;
} store;

bool operator< (const store &a, const store &b) {
	return a.day>b.day;
}

priority_queue<thing> q;
priority_queue<store> str;

int main  () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,wgt,val,dur,neww;
	for (int i=1;i<=n+m;i++) {
		scanf("%d",&a);
		if (a==1) {
			scanf("%d%d%d",&b,&wgt,&val);
			if (b==1) {
				q.push(thing{wgt,val,(int)2e9});
			} else if (b==2) {
				scanf("%d",&dur);
				q.push(thing{wgt,val,dur});
			} else if (b==3) {
				scanf("%d%d",&dur,&neww);
				q.push(thing{wgt,val,dur});
				str.push(store{dur,neww,val});
			}
		} else if (a==2) {
			while (!q.empty()&&q.top().dur<i) q.pop();
			if (!q.empty()) {
				printf("%d\n",q.top().val);
				q.pop();
			} else printf("0\n");
		}
		while (!str.empty()&&str.top().day==i) {
			q.push(thing{str.top().wgt,str.top().val,(int)2e9});
			str.pop();
		}
	}
	return 0;
}

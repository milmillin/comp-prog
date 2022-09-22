#include <cstdio>
#include <queue>

using namespace std;

bool deleted[1000100];

typedef struct {
	int score, idx;
} node;

bool operator< (const node &a, const node &b) {
	if (a.score==b.score) return a.idx<b.idx;
	return a.score<b.score;
}

priority_queue<node> q;
int scr[1000100];

int main () {
	int n,l,r;
	scanf("%d %d %d",&n,&l,&r);
	char x;
	int a,b;
	for (int i=0;i<l+r;i++) {
		scanf(" %c",&x);
		if (x=='L') {
			scanf("%d%d",&a,&b);
			scr[b]++;
			q.push(node{scr[b],b});
		} else if (x=='R') {
			while (!q.empty()&&deleted[q.top().idx]) q.pop();
			printf("%d\n",q.top().idx);
		} else if (x=='C') {
			scanf("%d%d",&a,&b);
			scr[b]+=3;
			q.push(node{scr[b],b});
		} else if (x=='D') {
			while (!q.empty()&&deleted[q.top().idx]) q.pop();
			deleted[q.top().idx]=true;
			q.pop();
		}
	}

}

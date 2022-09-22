#include <cstdio>
#include <queue>
#include <map>

using namespace std;

deque<int> q1;
deque<int> q2;
map<pair<deque<int>,deque<int> >,bool> mark;

//bool mark[20][20][20][20];

int main () {
	int n;
	scanf("%d",&n);
	int k1,k2;
	scanf("%d",&k1);
	int x;
	for (int i=0;i<k1;i++) {
		scanf("%d",&x);
		q1.push_front(x);
	}
	scanf("%d",&k2);
	for (int i=0;i<k2;i++) {
		scanf("%d",&x);
		q2.push_front(x);
	}
	int cnt=0;
	while (!q2.empty()&&!q1.empty()) {
		if (mark[make_pair(q1,q2)]) {
			printf("-1\n");
			return 0;
		}
		mark[make_pair(q1,q2)]=true;
		if (q1.back()>q2.back()) {
			q1.push_front(q2.back());
			q1.push_front(q1.back());
			q2.pop_back();
			q1.pop_back();
		} else {
			q2.push_front(q1.back());
			q2.push_front(q2.back());
			q2.pop_back();
			q1.pop_back();
		}
		cnt++;
	}
	printf("%d ",cnt);
	if (q1.empty()) {
		printf("2\n");
	} else {
		printf("1\n");
	}
	return 0;
}

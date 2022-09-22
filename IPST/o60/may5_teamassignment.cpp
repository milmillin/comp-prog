#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int tbl[100100];
int mic[100100];

int main () {
	int n,l,u;
	scanf("%d%d%d",&n,&l,&u);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	deque<int> q;
	for (int i=1;i<=l;i++) {
		while (!q.empty()&&tbl[q.back()]<=tbl[i]) q.pop_back();
		q.push_back(i);
		mic[i]=tbl[q.front()];
	}
	int cur=0;
	for (int i=l+1;i<=n;i++) {
		while (!q.empty()&&tbl[q.back()]<=tbl[i]) q.pop_back();
		q.push_back(i);
		while (!q.empty()&&q.front()<cur) q.pop_front();
		while (i-cur>l)	
	}
	return 0;
}

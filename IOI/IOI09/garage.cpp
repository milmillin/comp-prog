#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int rate[500];
int wgt[2010];

struct Rint {
	bool operator()(const int &a, const int &b) {
		return a>b;
	}
};

priority_queue<int,vector<int>,Rint> q;
int park[2010];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&rate[i]);
		q.push(i);
	}
	for (int i=1;i<=m;i++) {
		scanf("%d",&wgt[i]);
	}
	int x;
	long long ans=0;
	queue<int> car;
	for (int i=0;i<2*m;i++) {
		scanf("%d",&x);
		if (x>0) {
			car.push(x);
		} else {
			q.push(park[-x]);
			park[-x]=0;
		}
		while (!q.empty()&&!car.empty()) {
			ans+=(long long)wgt[car.front()]*rate[q.top()];
			park[car.front()]=q.top();
			car.pop();
			q.pop();
		}
	}
	printf("%lld\n",ans);
	return 0;
}

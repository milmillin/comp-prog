#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> pth[100100];

int recur(int idx) {	
	priority_queue<int,vector<int>,greater<int> > q;
	for (int i=0;i<(int)pth[idx].size();i++) {
		q.push(recur(pth[idx][i]));
	}
	int a,b;
	while (q.size()>1) {
		a=q.top();
		q.pop();
		b=q.top();
		q.pop();
		q.push(max(a,b)+1);
	}
	return (pth[idx].size()==1)?q.top()+1:((q.size())?q.top():0);
}

int main () {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		pth[x].push_back(i);
	}
	printf("%d\n",recur(1));
	return 0;
}
